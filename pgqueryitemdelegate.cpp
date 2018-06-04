#include "pgqueryitemdelegate.h"
#include "pgvalidator.h"
#include "generalitem.h"
#include <QEvent>
#include <QFocusEvent>
#include <QApplication>
#include <QAbstractItemView>

void PGQueryItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit* lineEdit = qobject_cast<QLineEdit*>(editor);
    PGValidator* validator = new PGValidator();
    QString value = lineEdit->text();
    int size = value.size();
    GeneralItem* item = static_cast<GeneralItem*>(index.internalPointer());
    QString modelValue = item->data(index.column()).toString();
    if(value != modelValue)  {
        if(validator->validate(value, size) == QValidator::Acceptable) {
            model->setData(index, value);
        } else {
            lineEdit->setText(value + "_invalid");
            model->setData(index, value + "_invalid");
        }
    }
}

void PGQueryItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::DisplayRole).toString();
    QLineEdit* line = static_cast<QLineEdit*>(editor);
    line->setText(value);
}
