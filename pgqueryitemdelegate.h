#ifndef PGQUERYITEMDELEGATE_H
#define PGQUERYITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QCompleter>
#include "database.h"

class PGQueryItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:

    QMap<QString, int> setCompleterData() const;
    Database* db;

     explicit PGQueryItemDelegate(QObject* parent = 0);

     QWidget* createEditor (QWidget* parent,
                            const QStyleOptionViewItem& option,
                            const QModelIndex& index ) const;

   protected:
     virtual bool eventFilter(QObject *object, QEvent *event);
};

#endif // PGQUERYITEMDELEGATE_H
