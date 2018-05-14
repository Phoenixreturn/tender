#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTreeView>
#include <QPushButton>
#include <QMessageBox>
#include <QTableView>
#include <QProgressBar>
#include <QStandardItemModel>
#include "customcombobox.h"
#include "treemodel.h"
#include "tablemodel.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void slotNoImpl()
      {
          QMessageBox::information(0, "Message", "Not implemented");
      }
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QToolBar* createToolbar();

private:
    Ui::MainWindow *ui;
    TreeModel* treeModel;
    TableModel* tableModel;
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
    QHBoxLayout *horizontalLayout_2;
    QPushButton *productAdd;
    QPushButton *productDelete;
    QItemSelectionModel *selectionModel;
    QItemSelectionModel *selectionTableModel;
    QMenu *refContextMenu;
    QAction *sampleAction;
    QProgressBar* progressBar;
    void createReferenceTab();
private slots:
    void openReference(bool ac);
    void closeReference(bool ac);
    void selection(QItemSelection, QItemSelection);
    void selectionTable(QItemSelection, QItemSelection);
    void insertRowToTreeModel(bool);
    void removeRowFromTreeModel(bool);

    void insertProductToTable(bool);
    void removeProductFromTable(bool);
};

#endif // MAINWINDOW_H
