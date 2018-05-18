#ifndef TREEMODEL_H
#define TREEMODEL_H

#include "generalmodel.h"

class TreeModel : public GeneralModel
{   
public:
    explicit TreeModel(QObject* parent = 0);
    void setupModelData();
private: 
    void setRootItem();
    void setupChildrenData(GeneralItem* item);
};

#endif // TREEMODEL_H
