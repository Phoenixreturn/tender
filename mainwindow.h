#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTreeView>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>
#include "customcombobox.h"
#include "treemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TreeModel* treeModel;
    Database *db;
    int referenceIndex;
    CustomCombobox *combo;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QTreeView *treeView;
    QPushButton *categoryAdd;
    QPushButton *categoryDelete;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QTableView *tableView;
    QStandardItemModel *tableModel;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *productAdd;
    QPushButton *productDelete;
    QItemSelectionModel *selectionModel;
    void createReferenceTab();
private slots:
    void openReference(bool ac);
    void closeReference(bool ac);
    void selection(QItemSelection, QItemSelection);
    void setTableModelData(int id);
};

#endif // MAINWINDOW_H
