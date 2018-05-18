#include "generalitem.h"

GeneralItem::GeneralItem(const QList<QVariant> &data, GeneralItem *parentItem, bool created)
{
    db = &Database::Instance();
    statements = &SqlStatements::Instance();
    if(!db->db.isOpen()) {
        db->connectToDataBase();
    }
    if(parentItem) {
        this->m_parentItem = parentItem;
    } else {
        this->m_parentItem = NULL;
    }
    this->m_itemData = data;
    if(created) {
        this->state = New;
    } else {
        this->state = Default;
    }
}

GeneralItem::~GeneralItem()
{
    qDeleteAll(m_childs);
    qDeleteAll(m_deletedChilds);
}

void GeneralItem::appendChild(GeneralItem *child)
{
     m_childs.append(child);
}

bool GeneralItem::removeChild(int row)
{
    m_childs[row]->setState(GeneralItem::Deleted);
    m_deletedChilds.append(m_childs[row]);
    m_childs.removeAt(row);
}

QList<GeneralItem *> GeneralItem::getChildren()
{
    return m_childs;
}

QList<GeneralItem *> GeneralItem::getDeletedChildren()
{
    return m_deletedChilds;
}

GeneralItem *GeneralItem::getChild(int row)
{
    return m_childs.value(row);
}

int GeneralItem::childCount() const
{
      return m_childs.count();
}

int GeneralItem::columnCount() const
{
     return m_itemData.count();
}

QVariant GeneralItem::data(int column) const
{
    return m_itemData.value(column);
}

void GeneralItem::setData(int column, QVariant value)
{
    if(!value.toString().isEmpty()) {
        m_itemData[column] = value;
        if(state != New) {
            state = Changed;
        }
    }
}

void GeneralItem::setState(GeneralItem::ObjectStates state)
{
      this->state = state;
}

GeneralItem::ObjectStates GeneralItem::getState()
{
      return state;
}

int GeneralItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childs.indexOf(const_cast<GeneralItem*>(this));

    return 0;
}

GeneralItem *GeneralItem::parentItem()
{
    return m_parentItem;
}

int GeneralItem::getId() const
{
    return id;
}

void GeneralItem::setId(int id)
{
    this->id = id;
}

int GeneralItem::createItem(GeneralItem *item)
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

void GeneralItem::updateItem(GeneralItem *item)
{

}

void GeneralItem::deleteItem(GeneralItem *item)
{

}
