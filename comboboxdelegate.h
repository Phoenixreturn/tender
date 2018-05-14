#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QStyledItemDelegate>
#include "database.h"

class ComboboxDelegate: public QStyledItemDelegate
{
    Q_OBJECT
   public:
       ComboboxDelegate(QObject* parent=0);
       ~ComboboxDelegate();

       void setComboboxData(QComboBox *cb) const;
       Database* db;

       virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
       virtual void setEditorData(QWidget* editor, const QModelIndex& index) const;
       virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
};

#endif // COMBOBOXDELEGATE_H
