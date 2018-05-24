#ifndef URLITEMDELEGATE_H
#define URLITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QTimer>

class UrlItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    UrlItemDelegate(QWidget *parent = 0);
//    virtual void	destroyEditor(QWidget *editor, const QModelIndex &index) const;
    virtual QWidget *	createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void setEditorData(QWidget * editor, const QModelIndex & index) const;
//    virtual void setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
//    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
protected:
    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model,
                             const QStyleOptionViewItem &option, const QModelIndex &index);
private:
    bool getEditState();
    QTimer *tmr;
    QString url;
    bool editState;
private slots:
    void openUrl();
    void setEditState(bool);
signals:
    void changeEditState(bool);
};

#endif // URLITEMDELEGATE_H
