#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
{
    db = &Database::Instance();
    bool ok = db->connectToDataBase();
    QList<QVariant> headerTable;
    headerTable.append("svd");
    headerTable.append("dsfvsdfvs");
    headers = new TableItem(headerTable);
    readSqlStatements();
    setupModelData(2);
}

TableModel::~TableModel()
{

}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TableItem *item = static_cast<TableItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return headers->data(section);

    return QVariant();
}

QModelIndex TableModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TableItem* item = tableItems.at(row);
//    if(item)
        return createIndex(row, column, item);
//    else
//        return QModelIndex();
}

QModelIndex TableModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return tableItems.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return headers->columnCount();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        TableItem* item = static_cast<TableItem*>(index.internalPointer());
        item->setData(0, value);
        emit(dataChanged(index, index));
        return true;
    }
    return false;
}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    QList<QVariant> data;
    data.append(QVariant("..."));
    data.append(QVariant("..."));
    TableItem* child = NULL;
    if(!parent.isValid()) {
         child = new TableItem(data, -1);
         createIndex(row, 0, child);
         beginInsertRows(parent, 1, 1);
         tableItems.append(child);
         endInsertRows();
    }
}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    QModelIndex temp = index(row,0,parent);
    TableItem* tempItem = static_cast<TableItem*>(temp.internalPointer());
    if(!parent.isValid()) {
        beginRemoveRows(temp.parent(), temp.row(), temp.row());
        endRemoveRows();
        return true;
    }
    return false;
}

void TableModel::setupModelData(int category)
{
    TableItem *temp;
    QSqlQuery parent_query(db->db);
    parent_query.prepare(category_products_query);
    parent_query.bindValue(0, 2);
    bool ok =  parent_query.exec();
    while(parent_query.next())
    {
        QList<QVariant> tempData;
        tempData << QVariant(parent_query.value(0)) << QVariant(parent_query.value(1));
        temp = new TableItem(tempData);
        tableItems.append(temp);
    }
}

int TableModel::readSqlStatements()
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
        if(!QString::compare(lst.first(), "category_products", Qt::CaseInsensitive)) {
             category_products_query = lst.last();
        }
    }

    file.close();
}
