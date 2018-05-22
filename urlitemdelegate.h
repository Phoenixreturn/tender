#ifndef URLITEMDELEGATE_H
#define URLITEMDELEGATE_H

#include <QStyledItemDelegate>

class UrlItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    UrlItemDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
//    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
//    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

#endif // URLITEMDELEGATE_H
