#include "customcombobox.h"
#include <QEvent>
#include <QMouseEvent>
#include <QScrollbar>
#include <QDebug>


CustomCombobox::CustomCombobox(QWidget *parent)
    : QComboBox(parent)
{
    this->setView(new QTreeView());
    view()->installEventFilter(this);
    view()->viewport()->installEventFilter(this);
}

CustomCombobox::~CustomCombobox()
{

}

bool CustomCombobox::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress && object == view()->viewport())
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        QModelIndex index = view()->indexAt(mouseEvent->pos());
        if (!view()->visualRect(index).contains(mouseEvent->pos()))
            skipNextHide = true;
    }
    return false;
}

void CustomCombobox::hidePopup()
{
    if (skipNextHide) {
        skipNextHide = false;        \
    }
    else
          QComboBox::hidePopup();
}
