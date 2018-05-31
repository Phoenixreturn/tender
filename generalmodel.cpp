#include "generalmodel.h"

GeneralModel::GeneralModel(QObject *parent)
    :QAbstractItemModel(parent)
{
    db = &Database::Instance();
    statements = &SqlStatements::Instance();
    if(!db->db.isOpen()) {
        db->connectToDataBase();
    }
}

GeneralModel::~GeneralModel()
{
    delete rootItem;
}

QVariant GeneralModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    GeneralItem *item = static_cast<GeneralItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags GeneralModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

QVariant GeneralModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex GeneralModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    GeneralItem *parentItem = NULL;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<GeneralItem*>(parent.internalPointer());

    GeneralItem *childItem = parentItem->getChild(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex GeneralModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    GeneralItem *childItem = static_cast<GeneralItem*>(index.internalPointer());
    GeneralItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int GeneralModel::rowCount(const QModelIndex &parent) const
{
    GeneralItem *parentItem;
    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<GeneralItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int GeneralModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<GeneralItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

bool GeneralModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        GeneralItem* item = static_cast<GeneralItem*>(index.internalPointer());
        item->setData(index.column(), value);
        emit(dataChanged(index, index));
        return true;
    }
    return false;
}

bool GeneralModel::insertRows(int row, int count, const QModelIndex &parent)
{
    QList<QVariant> data;
    for(int i = 0; i < rootItem->columnCount(); i++) {
        data.append(QVariant("..."));
    }
    GeneralItem* child = NULL;
    GeneralItem* parentItem = NULL;
    if(parent.isValid()) {
        parentItem = static_cast<GeneralItem*>(parent.internalPointer());
        child = new GeneralItem(data, parentItem, true);
    } else {
        child = new GeneralItem(data, rootItem, true);
    }
    if(child) {
        createIndex(row, 0, child);
    }
    beginInsertRows(parent, 1, 1);
    if(parentItem  != NULL) {
        parentItem->appendChild(child);
    } else {
        rootItem->appendChild(child);
    }
    endInsertRows();
}

bool GeneralModel::removeRows(int row, int count, const QModelIndex &parent)
{
    QModelIndex temp = index(row,0,parent);
    if(temp.isValid()) {
        if(!parent.isValid()) {
            beginRemoveRows(temp.parent(), temp.row(), temp.row());
            rootItem->removeChild(row);
            endRemoveRows();
            return true;
        }
        beginRemoveRows(temp.parent(), temp.row(), temp.row());
        GeneralItem* parentItem = static_cast<GeneralItem*>(parent.internalPointer());
        parentItem->removeChild(row);
        endRemoveRows();
        return true;
    }
    return false;
}

void GeneralModel::recursiveUpdate(GeneralItem *item)
{
    QList<GeneralItem*> children;
    children.append(item->getChildren());
    children.append(item->getDeletedChildren());
    foreach (GeneralItem* child, children) {
        switch(child->getState()) {
        case GeneralItem::New:
            item->createItem(child);
            recursiveUpdate(child);
            break;
        case GeneralItem::Changed:
            item->updateItem(child);
            recursiveUpdate(child);
            break;
        case GeneralItem::Deleted:
            removeDeletedFromDB(child);
            item->deleteItem(child);
            break;
        default:
            recursiveUpdate(child);
            break;
        }
    }
}

void GeneralModel::removeDeletedFromDB(GeneralItem *item)
{
    QList<GeneralItem*> items;
    items.append(item->getChildren());
    items.append(item->getDeletedChildren());
    foreach (GeneralItem* child, items) {
        QList<GeneralItem*> childs = child->getChildren();
        childs.append(child->getDeletedChildren());
        if(childs.size() == 0) {
            item->deleteItem(child);
        } else {
            removeDeletedFromDB(child);
            item->deleteItem(child);
        }
    }
}



void GeneralModel::updateModel()
{
    recursiveUpdate(rootItem);
}


void GeneralModel::emptyModelData(GeneralItem* item)
{
    foreach (GeneralItem* child, item->getChildren()) {
        emptyModelData(child);
    }    
    foreach (GeneralItem* child, item->getDeletedChildren()) {
        emptyModelData(child);
    }
    item->emptyLists();
    if(item != rootItem) {        
        delete(item);
    }
}
