#include "urlitemdelegate.h"
#include <QLabel>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <QEvent>
#include <QSizePolicy>
#include <QApplication>
#include <QDebug>
#include <QLineEdit>
#include "urlvalidator.h"

UrlItemDelegate::UrlItemDelegate(QWidget *parent)
    : QStyledItemDelegate(parent)
{
    url = "";
    tmr = NULL;
    editState = false;
    connect(this, SIGNAL(changeEditState(bool)), this, SLOT(setEditState(bool)));
}

QWidget *UrlItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    editor->setValidator(new UrlValidator);
    return editor;
}

void UrlItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QStyledItemDelegate::setEditorData(editor, index);
}

void UrlItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLabel *label = new QLabel;
    label->setText(index.data().toString());
    label->setTextFormat(Qt::RichText);
    label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    label->setMaximumWidth(option.rect.width());
    if (option.state & QStyle::State_MouseOver) {
        label->setStyleSheet("QLabel { background-color: transparent; font-weight: bold; text-decoration: underline; }");
        qApp->setOverrideCursor(Qt::PointingHandCursor);
    } else {        
        label->setStyleSheet("QLabel { background-color: transparent; font-weight: bold }");
        qApp->setOverrideCursor(Qt::ArrowCursor);
    }
    QPoint temp = option.rect.topLeft();
    temp.setY(temp.ry() + option.rect.height()/4);
    painter->translate(temp);
    label->render(painter);
    painter->translate(-temp);
}

void UrlItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit* lineEdit = qobject_cast<QLineEdit*>(editor);
    QString temp = lineEdit->text();
    QStyledItemDelegate::setModelData(editor, model, index);
}

bool UrlItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                  const QStyleOptionViewItem &option,
                                  const QModelIndex &index)
{
    if(event->type() == QEvent::MouseButtonDblClick) {
        if(tmr != NULL) {
            tmr->stop();
            delete tmr;
        }

        return QStyledItemDelegate::editorEvent(event, model, option, index);
    }

    if(event->type() == QEvent::MouseButtonPress) {
//        if(!this->getEditState()) {
            tmr = new QTimer();
            tmr->setInterval(200);
            url = index.data(Qt::DisplayRole).toString();
            connect(tmr, SIGNAL(timeout()), this, SLOT(openUrl()));
            tmr->start();

            return true;
//        }
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

bool UrlItemDelegate::getEditState()
{
    return editState;
}

void UrlItemDelegate::openUrl()
{
    QDesktopServices::openUrl(url);
    tmr->stop();
}

void UrlItemDelegate::setEditState(bool state)
{
    editState = state;
}
