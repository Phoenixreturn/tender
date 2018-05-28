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
}

QWidget *UrlItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    return editor;
}

void UrlItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::DisplayRole).toString();
    QLineEdit* line = static_cast<QLineEdit*>(editor);
    line->setText(value);
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
    int length = temp.size();
    UrlValidator* validator = new UrlValidator();
    if(validator->validate(temp, length) == QValidator::Acceptable) {
        model->setData(index, temp);
    } else {
        lineEdit->setText("");
        model->setData(index, "");
    }
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
            tmr = new QTimer();
            tmr->setInterval(200);
            url = index.data(Qt::DisplayRole).toString();
            connect(tmr, SIGNAL(timeout()), this, SLOT(openUrl()));
            tmr->start();
            return true;
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

void UrlItemDelegate::openUrl()
{
    QDesktopServices::openUrl(url);
    tmr->stop();
}
