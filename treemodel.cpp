#include "treeitem.h"
#include "treemodel.h"

#include <QStringList>

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    db = &Database::Instance();
    db->connectToDataBase();
    QList<QVariant> rootData;
    rootData << "name";
    rootItem = new TreeItem(rootData);
    readSqlStatements();
    setupModelData(rootItem);
}


TreeModel::~TreeModel()
{
    delete rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();
        TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
        item->setData(0, value);
        emit(dataChanged(index, index));
        return true;
    }
    return false;
}

bool TreeModel::insertRows(int row, int count, const QModelIndex &parent)
{
    QList<QVariant> data;
    data.append(QVariant("..."));
    data.append(QVariant("..."));
    TreeItem* child = NULL;
    TreeItem* parentItem = NULL;
    if(parent.isValid()) {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
        child = new TreeItem(data, -1, parentItem);
    } else {
        child = new TreeItem(data, -1, rootItem);
    }
    if(child) {
        createIndex(row, 0, child);
    }
    beginInsertRows(parent, 1, 1);
    if(parentItem != NULL) {
        parentItem->appendChild(child);
    } else {
        rootItem->appendChild(child);
    }
     endInsertRows();

}

bool TreeModel::removeRows(int row,int count, const QModelIndex &parent)
{
    QModelIndex temp = index(row,0,parent);
    if(!parent.isValid()) {
        beginRemoveRows(temp.parent(), temp.row(), temp.row());
        rootItem->removeChild(row);
        endRemoveRows();
        return true;
    }
    beginRemoveRows(temp.parent(), temp.row(), temp.row());
    TreeItem* parentItem = static_cast<TreeItem*>(parent.internalPointer());
    parentItem->removeChild(row);
    endRemoveRows();
    return true;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

void TreeModel::setupModelData(TreeItem *parent)
{
    TreeItem* temp;
    QSqlQuery parent_query(db->db);
    parent_query.prepare(parent_category_query);
    bool ok =  parent_query.exec();
    while(parent_query.next())
    {
        QList<QVariant> tempData;
        tempData << QVariant(parent_query.value(1)) << QVariant(parent_query.value(3));
        temp = new TreeItem(tempData, parent_query.value(0).toInt(), parent);
        parent->appendChild(temp);
        setupChilds(temp);
    }
}

void TreeModel::setupChilds(TreeItem *parent)
{
    TreeItem* temp;
    QSqlQuery category_by_parent(db->db);
    category_by_parent.prepare(category_by_parent_query);
    category_by_parent.bindValue(0, parent->getId());
    category_by_parent.exec();
    while(category_by_parent.next())
    {
        QList<QVariant> tempData;
        tempData << QVariant(category_by_parent.value(1)) << QVariant(category_by_parent.value(3));
        temp = new TreeItem(tempData, category_by_parent.value(0).toInt(), parent);
        parent->appendChild(temp);
        setupChilds(temp);
    }
}

int TreeModel::readSqlStatements()
{
    QFile file(QUERIES);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;

    while (!file.atEnd()) {
        const QByteArray line = file.readLine();
        const QString str( line );
        const QStringList lst = str.split(QRegExp("=="));
        if (lst.size() != 2) {
            qDebug() << "error";
            return -2;
        }
        if(!QString::compare(lst.first(), "parent_category", Qt::CaseInsensitive)) {
             parent_category_query = lst.last();
        }
        if(!QString::compare(lst.first(), "category_by_parent", Qt::CaseInsensitive)) {
             category_by_parent_query = lst.last();          
        }
        if(!QString::compare(lst.first(), "add_category", Qt::CaseInsensitive)) {
             add_category = lst.last();
        }
        if(!QString::compare(lst.first(), "update_category", Qt::CaseInsensitive)) {
             update_category = lst.last();
        }
        if(!QString::compare(lst.first(), "create_category", Qt::CaseInsensitive)) {
             create_category = lst.last();
        }
        if(!QString::compare(lst.first(), "delete_category", Qt::CaseInsensitive)) {
             delete_category = lst.last();
        }
        if(!QString::compare(lst.first(), "contains_category_in_mapping", Qt::CaseInsensitive)) {
             contains_category_in_mapping = lst.last();
        }
        if(!QString::compare(lst.first(), "remove_mapping", Qt::CaseInsensitive)) {
             remove_mapping = lst.last();
        }
        if(!QString::compare(lst.first(), "update_mapping", Qt::CaseInsensitive)) {
             update_mapping = lst.last();
        }
    }

    file.close();
}

int TreeModel::createTreeItem(TreeItem *item)
{
    QSqlQuery create_category(db->db);
    create_category.prepare(this->create_category);
    create_category.bindValue(0, item->data(0));
    if(item->parentItem()->getId() != -1) {
         create_category.bindValue(1, item->parentItem()->getId());
    } else {
        create_category.bindValue(1, QVariant(QVariant::Int));
    }
    create_category.bindValue(2, item->data(1));
    create_category.exec();
    int id = create_category.lastInsertId().toInt();

    item->setId(id);

    return id;
}

void TreeModel::updateTreeItem(TreeItem *item)
{
    QSqlQuery update_category(db->db);
    update_category.prepare(this->update_category);
    update_category.bindValue(0, item->data(0));
    update_category.bindValue(1, item->data(1));
    update_category.bindValue(2, item->getId());
    update_category.exec();
}

void TreeModel::deleteTreeItem(TreeItem *item)
{

}

void TreeModel::recursiveUpdate(TreeItem *item)
{
    foreach (TreeItem* child, item->getChilds()) {
        switch(child->getState())   {
        case TreeItem::New:
            createTreeItem(child);
            recursiveUpdate(child);
            break;
        case TreeItem::Changed:
            updateTreeItem(child);
            recursiveUpdate(child);
            break;
        case TreeItem::Deleted:
            deleteTreeItem();
            recursiveUpdate(child);
            break;
        default:
            recursiveUpdate(child);
            break;
        }
    }
}

void TreeModel::updateModel()
{
   this->recursiveUpdate(rootItem);
}
