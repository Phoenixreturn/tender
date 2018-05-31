#include "tableitem.h"

GeneralItem* TableItem::category = NULL;

TableItem::TableItem(const QList<QVariant> &data, TableItem *parentItem, bool created)
    : GeneralItem(data, parentItem, created)
{

}

int TableItem::createItem(GeneralItem *item)
{
    QSqlQuery create_product(db->db);
    create_product.prepare(statements->add_product_query);
    create_product.bindValue(0, item->data(0));
    create_product.bindValue(1, item->data(1));
    create_product.bindValue(2, item->data(2));
    create_product.bindValue(3, item->data(3));
    create_product.bindValue(4, item->data(4));
    create_product.bindValue(5, item->data(5));
    create_product.exec();
    int id = create_product.lastInsertId().toInt();
    item->setId(id);
    int category_id = TableItem::getCategory()->getId();

    QSqlQuery update_mapping(db->db);
    update_mapping.prepare(statements->update_mapping_query);
    update_mapping.bindValue(0, QVariant(id));
    update_mapping.bindValue(1, QVariant(category_id));
    update_mapping.exec();

    return id;
}

void TableItem::updateItem(GeneralItem *item)
{
    QSqlQuery update_product(db->db);
    update_product.prepare(statements->update_product_query);
    update_product.bindValue(0, item->data(0));
    update_product.bindValue(1, item->data(1));
    update_product.bindValue(2, item->data(2));
    update_product.bindValue(3, item->data(3));
    update_product.bindValue(4, item->data(4));
    update_product.bindValue(5, item->data(5));
    update_product.bindValue(6, item->getId());
}

void TableItem::deleteItem(GeneralItem *item)
{
    int category_id = TableItem::getCategory()->getId();
    QSqlQuery delete_in_mapping(db->db);
    delete_in_mapping.prepare(statements->delete_in_mapping_query);
    delete_in_mapping.bindValue(0, item->getId());
    delete_in_mapping.bindValue(1, category_id);
    delete_in_mapping.exec();

    QSqlQuery contains_in_mapping(db->db);
    contains_in_mapping.prepare(statements->contains_product_in_mapping_query);
    contains_in_mapping.bindValue(0, item->getId());
    contains_in_mapping.exec();
    if(contains_in_mapping.size() == 0) {
        QSqlQuery delete_product(db->db);
        delete_product.prepare(statements->delete_product_query);
        delete_product.bindValue(0, item->getId());
        delete_product.exec();
    }
}

void TableItem::setCategory(GeneralItem *category)
{
    TableItem::category = category;
}

GeneralItem *TableItem::getCategory()
{
    return TableItem::category;
}
