#include <QStringList>
#include "treeitem.h"

//! [0]
TreeItem::TreeItem(const QList<QVariant> &data, int id, TreeItem *parent)
{
    this->m_parentItem = parent;
    this->m_itemData = data;
    this->id = id;
}
//! [0]

//! [1]
TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}
//! [1]

//! [2]
void TreeItem::appendChild(TreeItem *item)
{
    m_childItems.append(item);
}
//! [2]

//! [3]
TreeItem *TreeItem::child(int row)
{
    return m_childItems.value(row);
}
//! [3]

//! [4]
int TreeItem::childCount() const
{
    return m_childItems.count();
}
//! [4]

//! [5]
int TreeItem::columnCount() const
{
    return m_itemData.count();
}
//! [5]

//! [6]
QVariant TreeItem::data(int column) const
{
    return m_itemData.value(column);
}
//! [6]

//! [7]
TreeItem *TreeItem::parentItem()
{
    return m_parentItem;
}
//! [7]

//! [8]
int TreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

int TreeItem::getId() const
{
    return id;
}
//! [8]
