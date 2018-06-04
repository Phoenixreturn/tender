#ifndef PGQUERYITEMDELEGATE_H
#define PGQUERYITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QLineEdit>
#include "pgvalidator.h"

class PGQueryItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit PGQueryItemDelegate(QObject* parent = 0) : QStyledItemDelegate(parent) {}
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    virtual void setEditorData(QWidget * editor, const QModelIndex & index) const;

};

#endif // PGQUERYITEMDELEGATE_H
