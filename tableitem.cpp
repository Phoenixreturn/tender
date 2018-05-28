#include "tableitem.h"

TableItem::TableItem(const QList<QVariant> &data, TableItem *parentItem, bool created)
    : GeneralItem(data, parentItem, created)
{

}

int TableItem::createItem(GeneralItem *item)
{
    QSqlQuery create_category(db->db);
    create_category.prepare(statements->add_category_query);
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

void TableItem::updateItem(GeneralItem *item)
{

}

void TableItem::deleteItem(GeneralItem *item)
{

}
