#ifndef TABLEITEM_H
#define TABLEITEM_H

#include "generalitem.h"

class TableItem : public GeneralItem
{
public:
    explicit TableItem(const QList<QVariant> &data,  TableItem *parentItem = NULL, bool created = false);

    virtual int createItem(GeneralItem* item);
    virtual void updateItem(GeneralItem* item);
    virtual void deleteItem(GeneralItem* item);
};

#endif // TABLEITEM_H
