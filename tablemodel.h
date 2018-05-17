#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractItemModel>
#include "database.h"
#include "tableitem.h"

class TableModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject *parent = 0);
    ~TableModel();

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    void setupModelData(int category = -1);
    void emptyModelData();
private:   
    int readSqlStatements();

    Database* db;
    QList<TableItem*> tableItems;
    QList<TableItem*> deletedItems;
    TableItem* headers;
    int categoryId;

    QString parent_category_query;
    QString category_by_parent_query;
    QString category_products_query;
    QString add_category;
    QString add_product;
    QString remove_mapping;
    QString contains_category_in_mapping;
    QString contains_product_in_mapping;
public slots:
    void updateModel();
};

#endif // TABLEMODEL_H
