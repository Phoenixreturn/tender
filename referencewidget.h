#ifndef REFERENCEWIDGET_H
#define REFERENCEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTreeView>
#include <QTableView>
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include "treemodel.h"
#include "tablemodel.h"
#include "pgqueryitemdelegate.h"

class ReferenceWidget: public QWidget
{
    Q_OBJECT
public:
    ReferenceWidget();  
private slots:
    void selectionTree(QItemSelection, QItemSelection);
    void selectionTable(QItemSelection, QItemSelection);
    void insertRowToTreeModel(bool);
    void removeRowFromTreeModel(bool);
    void insertProductToTable(bool);
    void removeProductFromTable(bool);
private:
    void createLayouts();
    void createButtons();
    void setContextMenu();
    void setItemDelegates();
    void setViewModels();

    //models
    TreeModel* treeModel;
    TableModel* tableModel;
    QItemSelectionModel *selectionTreeModel;
    QItemSelectionModel *selectionTableModel;
    QTreeView *treeView;
    QTableView *tableView;

    //layouts
    QVBoxLayout *verticalTreeLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalTableLayout;
    QHBoxLayout *horizontalButtonTableLayout;

    // buttons
    QPushButton *categoryAdd;
    QPushButton *categoryDelete;
    QPushButton *productAdd;
    QPushButton *productDelete;

    // context menu
    QMenu *refContextMenu;
    QAction *sampleAction;
};

#endif // REFERENCEWIDGET_H
