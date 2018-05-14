#include "tableitem.h"


TableItem::TableItem(const QList<QVariant> &data, int id)
{
    tableItem_data = data;
    if(id != 0) {
        this->categoryId = id;
    } else {
        this->categoryId = id;
    }
}

TableItem::~TableItem()
{

}

int TableItem::columnCount() const
{
   return tableItem_data.size();
}

QVariant TableItem::data(int column) const
{
     return tableItem_data.value(column);
}

void TableItem::setData(int column, QVariant value)
{
    if(!value.toString().isEmpty()) {
        tableItem_data[column] = value;
        newFlag = true;
    }
}

int TableItem::getCategoryId() const
{
    return categoryId;
}
