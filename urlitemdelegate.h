#ifndef URLITEMDELEGATE_H
#define URLITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QTimer>

class UrlItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    UrlItemDelegate(QWidget *parent = 0);
    virtual QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void setEditorData(QWidget * editor, const QModelIndex & index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
protected:
    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model,
                             const QStyleOptionViewItem &option, const QModelIndex &index);
private:
    QTimer *tmr;
    QString url;
private slots:
    void openUrl();
};

#endif // URLITEMDELEGATE_H
