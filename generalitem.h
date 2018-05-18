#ifndef GENERALITEM_H
#define GENERALITEM_H

#include <QObject>
#include <QList>
#include <sqlstatements.h>
#include <database.h>

class GeneralItem : public QObject
{
    Q_OBJECT
    Q_ENUMS(ObjectStates)
public:
    explicit GeneralItem(const QList<QVariant> &data,  GeneralItem *parentItem = NULL, bool created = false);
    ~GeneralItem();

    enum ObjectStates
        {
           Default,
           Changed,
           Deleted,
           New
        };
    GeneralItem();
    Database* db;
    SqlStatements* statements;

    void appendChild(GeneralItem* child);
    bool removeChild(int row);

    QList<GeneralItem*> getChildren();
    QList<GeneralItem*> getDeletedChildren();
    GeneralItem* getChild(int row);
    int childCount() const;
    int columnCount() const;

    QVariant data(int column) const;
    void setData(int column, QVariant value);

    void setState(ObjectStates state);
    ObjectStates getState();

    int row() const;
    GeneralItem* parentItem();

    int getId() const;
    void setId(int id);

    int createItem(GeneralItem* item);
    void updateItem(GeneralItem* item);
    void deleteItem(GeneralItem* item);
private:
    ObjectStates state;
    int id;
    QList<GeneralItem*> m_childs;
    QList<GeneralItem*> m_deletedChilds;
    QList<QVariant> m_itemData;
    GeneralItem* m_parentItem;
};

#endif // GENERALITEM_H
