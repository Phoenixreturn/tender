#ifndef MODEL_H
#define MODEL_H

#include <QAbstractItemModel>

class Model : public QAbstractItemModel
{
public:
    Model(QObject *parent = 0);
    virtual QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
    virtual int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    virtual int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    virtual QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    virtual QModelIndex parent ( const QModelIndex & index ) const;
};

#endif // MODEL_H
