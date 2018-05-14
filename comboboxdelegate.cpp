#include "comboboxdelegate.h"
#include <QComboBox>

ComboboxDelegate::ComboboxDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
    db = &Database::Instance();
    bool ok = db->connectToDataBase();
}


ComboboxDelegate::~ComboboxDelegate()
{
}

void ComboboxDelegate::setComboboxData(QComboBox *cb) const
{
    cb->addItem("...");
    QSqlQuery category_by_parent(db->db);
    category_by_parent.prepare("SELECT * FROM `products`");
//    category_by_parent.bindValue(0, parent->getId());
    category_by_parent.exec();
    while(category_by_parent.next())
    {
        cb->addItem(category_by_parent.value(0).toString());
    }
}


QWidget* ComboboxDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    // ComboBox only in column 1
    if (index.column() != 0)
        return QStyledItemDelegate::createEditor(parent, option, index);

    // Create the combobox and populate it
    QComboBox* cb = new QComboBox(parent);
    int row = index.row();
    setComboboxData(cb);
    cb->setEditable(true);
    return cb;
}


void ComboboxDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    if (QComboBox* cb = qobject_cast<QComboBox*>(editor)) {
       // get the index of the text in the combobox that matches the current value of the itenm
       QString currentText = index.data(Qt::EditRole).toString();
       int cbIndex = cb->findText(currentText);
       // if it is valid, adjust the combobox
       if (cbIndex >= 0) {
        cb->setCurrentIndex(cbIndex);
       }
    } else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}


void ComboboxDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    if (QComboBox* cb = qobject_cast<QComboBox*>(editor))
        // save the current text of the combo box as the current value of the item
        model->setData(index, cb->currentText(), Qt::EditRole);
    else
        QStyledItemDelegate::setModelData(editor, model, index);
}
