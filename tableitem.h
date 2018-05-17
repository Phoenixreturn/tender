#ifndef TABLEITEM_H
#define TABLEITEM_H

#include <QList>
#include <QObject>

class TableItem : public QObject
{
    Q_OBJECT
    Q_ENUMS(ObjectStates)
public:
    enum ObjectStates
        {
           Default,
           Changed,
           Deleted,
           New
        };
    explicit TableItem(const QList<QVariant> &data, bool created = false);
    ~TableItem();

    int columnCount() const;
    QVariant data(int column) const;
    void setData(int column, QVariant value);
    void setState(ObjectStates state);
    ObjectStates getState();

private:    
    ObjectStates state;
    QString oldName;
    QList<QVariant> tableItem_data;
};

#endif // TABLEITEM_H
