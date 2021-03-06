#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
{
    db = &Database::Instance();
    db->connectToDataBase();
    QList<QVariant> headerTable;
    headerTable.append("Наименование");
    headerTable.append("Единица");
    headerTable.append("Цена");
    headerTable.append("Валюта");
    headers = new TableItem(headerTable);
    readSqlStatements();
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
    TableItem* item = NULL;
    if(0 <= row < tableItems.size()) {
        item = tableItems.at(row);
    }
    if(item)
        return createIndex(row, column, item);
    else
        return QModelIndex();
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
        item->setData(index.column(), value);
        emit(dataChanged(index, index));
        return true;
    }
    return false;
}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    QList<QVariant> data;
    //число элементов списка должно быть таким же как число столбцов
    data.append(QVariant("..."));
    data.append(QVariant("..."));
    data.append(QVariant("..."));
    data.append(QVariant("..."));
    TableItem* child = NULL;
    if(!parent.isValid()) {
         child = new TableItem(data, true);
         createIndex(row, 0, child);
         beginInsertRows(parent, 1, 1);
         tableItems.append(child);
         endInsertRows();
    }
}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    QModelIndex temp = index(row,0,parent);
    if(!parent.isValid()) {
        beginRemoveRows(temp.parent(), temp.row(), temp.row());       
        tableItems[row]->setState(TableItem::Deleted);
        deletedItems.append(tableItems[row]);
        tableItems.removeAt(row);
        endRemoveRows();
        return true;
    }
    return false;
}

void TableModel::setupModelData(int category)
{
    this->emptyModelData();
    if(category != -1) {
        TableItem *temp;
        QSqlQuery products_query(db->db);
        products_query.prepare(category_products_query);
        products_query.bindValue(0, category);
        products_query.exec();
        while(products_query.next())
        {
            QList<QVariant> tempData;
            tempData << QVariant(products_query.value(3)) << QVariant(products_query.value(4))
                     << QVariant(products_query.value(5)) << QVariant(products_query.value(6));
            temp = new TableItem(tempData);
            tableItems.append(temp);
        }
    }
}

void TableModel::emptyModelData()
{
    beginResetModel();
    tableItems.clear();
    categoryId = -1;
    endResetModel();
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

void TableModel::updateModel()
{
//    this->emptyModelData();
//    if(category != -1) {
//        TableItem *temp;
//        QSqlQuery products_query(db->db);
//        products_query.prepare(category_products_query);
//        products_query.bindValue(0, category);
//        products_query.exec();
//        while(products_query.next())
//        {
//            QList<QVariant> tempData;
//            tempData << QVariant(products_query.value(3)) << QVariant(products_query.value(4))
//                     << QVariant(products_query.value(5)) << QVariant(products_query.value(6));
//            temp = new TableItem(tempData);
//            tableItems.append(temp);
//        }
//    }
}
