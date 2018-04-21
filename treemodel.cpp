#include "treeitem.h"
#include "treemodel.h"

#include <QStringList>

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    db = &Database::Instance();
    bool ok = db->connectToDataBase();
    QList<QVariant> rootData;
    rootData << "name" << "description";
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

    return QAbstractItemModel::flags(index);
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
        const QStringList lst = str.split('=');
        if (lst.size() != 2) {
            qDebug() << "error";
            return -2;
        }
        if(!QString::compare(lst.first(), "parent_category", Qt::CaseInsensitive)) {
             parent_category_query = lst.last();
        }
        if(!QString::compare(lst.first(), "category_by_parent", Qt::CaseInsensitive)) {
             category_by_parent_query = lst.last();
             category_by_parent_query.remove(QRegExp("[\\n\\t\\r]"));
             category_by_parent_query += "=?";
        }
    }

    file.close();
}