#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include "generalmodel.h"

class TableModel : public GeneralModel
{
public:
    explicit TableModel(int categoryId, QObject* parent = 0);
    void setCategoryId(int id);
    int getCategoryId();
    void setupModelData();
private:
    int categoryId;
    void setRootItem();
};

#endif // TABLEMODEL_H
