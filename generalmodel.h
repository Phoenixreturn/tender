#ifndef GENERALMODEL_H
#define GENERALMODEL_H

#include <QAbstractItemModel>
#include "database.h"
#include "sqlstatements.h"
#include "generalitem.h"

class GeneralModel : public QAbstractItemModel
{
    Q_OBJECT
protected:
    Database* db;
    SqlStatements* statements;
    void emptyModelData(GeneralItem* item);
public:
    GeneralItem *rootItem;
public:    
   explicit GeneralModel(QObject *parent = 0);
   ~GeneralModel();

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
   virtual void setupModelData() = 0;
private:    
    virtual void setRootItem() = 0;
    void recursiveUpdate(GeneralItem* item);
public slots:
   void updateModel();
};

#endif // GENERALMODEL_H
