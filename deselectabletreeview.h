#ifndef DESELECTABLETREEVIEW_H
#define DESELECTABLETREEVIEW_H
#include "QTreeView"
#include "QMouseEvent"

class DeselectableTreeView : public QTreeView
{
public:
    DeselectableTreeView(QWidget *parent) : QTreeView(parent) {}
    ~DeselectableTreeView() {}

private:
    virtual void mousePressEvent(QMouseEvent *event) {
        QModelIndex item = indexAt(event->pos());


       if ((item.row() == -1 && item.column() == -1))
       {
           clearSelection();
           const QModelIndex index;
           selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);
       }
    QTreeView::mousePressEvent(event);
    }
};

#endif // DESELECTABLETREEVIEW_H
