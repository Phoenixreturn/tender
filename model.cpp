#include "model.h"

Model::Model(QObject *parent) :
    QAbstractItemModel(parent)
{

}

QModelIndex Model::index(int row, int column, const QModelIndex &parent) const
{

}

int Model::rowCount(const QModelIndex &parent) const
{
}

int Model::columnCount(const QModelIndex &parent) const
{

}

QVariant Model::data(const QModelIndex &index, int role) const
{

}

QModelIndex Model::parent(const QModelIndex &index) const
{

}
