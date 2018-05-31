#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include "generalmodel.h"
#include "tableitem.h"

class TableModel : public GeneralModel
{
public:
    explicit TableModel(GeneralItem* category = NULL, QObject* parent = 0);
    void setupModelData();
private:
    void setRootItem();
};

#endif // TABLEMODEL_H
