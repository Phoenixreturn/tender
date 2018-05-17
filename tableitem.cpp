#include "tableitem.h"


TableItem::TableItem(const QList<QVariant> &data, bool created)
{
    tableItem_data = data;
    if(created) {
        state = New;
    } else {        
        state = Default;
        oldName = data.at(0).toString();
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
        if(state != New) {
            state = Changed;
        }
    }
}

void TableItem::setState(TableItem::ObjectStates state)
{
    this->state = state;
}

TableItem::ObjectStates TableItem::getState()
{
    return state;
}
