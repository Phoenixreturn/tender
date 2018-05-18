#include "pgqueryitemdelegate.h"
#include <QEvent>
#include <QFocusEvent>
#include <QApplication>
#include <QAbstractItemView>

QMap<QString, int> PGQueryItemDelegate::setCompleterData() const
{
    QMap<QString, int> values;
    QSqlQuery category_by_parent(db->db);
    category_by_parent.prepare(statements->all_products_query);
    category_by_parent.exec();
    int i = 0;
    while(category_by_parent.next())
    {
        values.insert(category_by_parent.value(1).toString(), i);
        i++;
    }
    return values;
}

PGQueryItemDelegate::PGQueryItemDelegate(QObject* parent):QStyledItemDelegate(parent)
{
    db = &Database::Instance();
    statements = &SqlStatements::Instance();
    if(!db->db.isOpen()) {
        db->connectToDataBase();
    }
}

QWidget *PGQueryItemDelegate::createEditor(QWidget *parent,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex & index ) const
{
    if (index.column() != 0)
        return QStyledItemDelegate::createEditor(parent, option, index);
  QWidget *editor = QStyledItemDelegate::createEditor(parent, option, index);
  QLineEdit* lineEdit = qobject_cast<QLineEdit*>(editor);
  if (lineEdit) {
    QCompleter* completer = new QCompleter(setCompleterData().keys(), lineEdit);
    completer->setCompletionColumn(0);
    completer->setModelSorting(QCompleter::CaseSensitivelySortedModel);
    completer->setCompletionMode(QCompleter::InlineCompletion);
    completer->setFilterMode(Qt::MatchContains);
    lineEdit->setCompleter(completer);
    lineEdit->setMaxLength(30);
    return lineEdit;
  }

  return editor;
}

bool PGQueryItemDelegate::eventFilter(QObject *object, QEvent *event)
{
  if (event->type() == QEvent::FocusIn) {
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(object);
    if (lineEdit) {
      if (lineEdit->completer())
        lineEdit->completer()->setCompletionMode(QCompleter::PopupCompletion);
    }
  }
  if (event->type() == QEvent::FocusOut) {
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(object);
    if (lineEdit) {
      QFocusEvent *focusEvent = static_cast<QFocusEvent*>(event);
      if (lineEdit->completer()) {
        if (QApplication::activeWindow() == lineEdit->completer()->popup())
          return true;
      }
    }
  }
  return QStyledItemDelegate::eventFilter(object, event);
}
