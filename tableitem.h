#ifndef TABLEITEM_H
#define TABLEITEM_H

#include <QList>

class TableItem
{
public:
    explicit TableItem(const QList<QVariant> &data, int id=0);
    ~TableItem();

    int columnCount() const;
    QVariant data(int column) const;
    void setData(int column, QVariant value);
private:
    bool newFlag;
    QList<QVariant> tableItem_data;
};

#endif // TABLEITEM_H
