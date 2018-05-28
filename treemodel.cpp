#include "treemodel.h"

TreeModel::TreeModel(QObject *parent)
    :GeneralModel(parent)
{
    setRootItem();
    setupModelData();
}

void TreeModel::setupModelData()
{
    setupChildrenData(rootItem);
}

void TreeModel::setRootItem()
{
    QList<QVariant> data;
    data.append("Имя");
    data.append("Описание");
    rootItem = new GeneralItem(data);
    rootItem->setId(-1);
}

void TreeModel::setupChildrenData(GeneralItem *item)
{
    GeneralItem* temp = NULL;
    QString query = statements->category_by_parent_query.simplified();
    QSqlQuery category_by_parent(db->db);
    if(item->parentItem() == NULL) {
        query += " IS NULL";
        category_by_parent.prepare(query);
    } else {
        query += "=?";
        category_by_parent.prepare(query);
        category_by_parent.bindValue(0, item->getId());
    }
    category_by_parent.exec();
    while(category_by_parent.next())
    {
        QList<QVariant> tempData;
        tempData << QVariant(category_by_parent.value(1)) << QVariant(category_by_parent.value(3));
        temp = new GeneralItem(tempData, item);
        temp->setId(QVariant(category_by_parent.value(0)).toInt());
        item->appendChild(temp);
        setupChildrenData(temp);
    }
}
