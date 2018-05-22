#include "urlitemdelegate.h"
#include <QLabel>
#include <QPainter>

void UrlItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLabel *label = new QLabel;
    label->setText(index.data().toString());
    label->setTextFormat(Qt::RichText);
    label->setGeometry(option.rect);
    label->setStyleSheet("QLabel { background-color : transparent; }");

    painter->translate(option.rect.topLeft());
    label->render(painter);
    painter->translate(-option.rect.topLeft());
}
