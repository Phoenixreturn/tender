#include "tablemodel.h"

TableModel::TableModel(int categoryId, QObject *parent)
    : GeneralModel(parent)
{
    setCategoryId(categoryId);
    setRootItem();
    setupModelData();
}

void TableModel::setCategoryId(int id)
{
    categoryId = id;
}

int TableModel::getCategoryId()
{
return categoryId;
}

void TableModel::setupModelData()
{     
    beginResetModel();
    emptyModelData(rootItem);
    if(categoryId != -1) {
        GeneralItem *temp = NULL;
        QSqlQuery products_query(db->db);
        products_query.prepare(statements->category_products_query);
        products_query.bindValue(0, categoryId);
        products_query.exec();
        while(products_query.next())
        {
            QList<QVariant> tempData;
            tempData << QVariant(products_query.value(1)) << QVariant(products_query.value(2))
                     << QVariant(products_query.value(3)) << QVariant(products_query.value(4))
                     << QVariant(products_query.value(5)) << QVariant(products_query.value(6));
            temp = new GeneralItem(tempData, rootItem);
            temp->setId(QVariant(products_query.value(0)).toInt());
            rootItem->appendChild(temp);
        }
    }
    endResetModel();
}

void TableModel::setRootItem()
{
    QList<QVariant> data;
    data.append("Наименование");
    data.append("Единица");
    data.append("Цена");
    data.append("Валюта");
    data.append("Источник");
    data.append("Описание");
    rootItem = new GeneralItem(data);
    rootItem->setId(-1);
}
