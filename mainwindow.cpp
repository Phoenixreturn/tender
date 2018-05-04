#include "mainwindow.h"
#include "treeitem.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    db = &Database::Instance();
    bool ok = db->connectToDataBase();
    treeModel = new TreeModel();
    tableModel = new QStandardItemModel();
    createReferenceTab();
    ui->setupUi(this);
    combo = new CustomCombobox(ui->tabWidget->currentWidget());
    refContextMenu = new QMenu(treeView);
    treeView->setContextMenuPolicy(Qt::ActionsContextMenu);
    sampleAction = new QAction("Sample Action", refContextMenu);
    treeView->addAction(sampleAction);
    treeView->setModel(treeModel);
    tableView->setModel(tableModel);
    selectionModel = treeView->selectionModel();
    selectionTableModel = tableView->selectionModel();
    combo->setModel(treeModel);
    combo->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);
    combo->setMinimumWidth(200);
    combo->show();

    connect(selectionModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(selection(QItemSelection,QItemSelection)));
    connect(selectionTableModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(selectionTable(QItemSelection,QItemSelection)));
    connect(ui->openReference,SIGNAL(triggered(bool)),this, SLOT(openReference(bool)));
    connect(ui->closeReference,SIGNAL(triggered(bool)),this, SLOT(closeReference(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createReferenceTab()
{
    horizontalLayoutWidget = new QWidget();
    horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
    horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    verticalLayout = new QVBoxLayout();
    verticalLayout->setSpacing(6);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    treeView = new QTreeView(horizontalLayoutWidget);
    treeView->setObjectName(QStringLiteral("treeView"));
    treeView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    verticalLayout->addWidget(treeView);

    categoryAdd = new QPushButton(horizontalLayoutWidget);
    categoryAdd->setObjectName(QStringLiteral("categoryAdd"));
    categoryAdd->setEnabled(false);
    QIcon icon;
    icon.addFile(QStringLiteral(":/icons/add_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    categoryAdd->setIcon(icon);

    verticalLayout->addWidget(categoryAdd);

    categoryDelete = new QPushButton(horizontalLayoutWidget);
    categoryDelete->setObjectName(QStringLiteral("categoryDelete"));
    categoryDelete->setEnabled(false);
    QIcon icon1;
    icon1.addFile(QStringLiteral(":/icons/delete_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    categoryDelete->setIcon(icon1);

    verticalLayout->addWidget(categoryDelete);

    horizontalLayout->addLayout(verticalLayout);

    verticalLayout_2 = new QVBoxLayout();
    verticalLayout_2->setSpacing(6);
    verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
    tableView = new QTableView(horizontalLayoutWidget);
    tableView->setObjectName(QStringLiteral("tableView"));
    tableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    verticalLayout_2->addWidget(tableView);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setSpacing(6);
    horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
    productAdd = new QPushButton(horizontalLayoutWidget);
    productAdd->setObjectName(QStringLiteral("productAdd"));
    productAdd->setEnabled(false);
    productAdd->setIcon(icon);

    horizontalLayout_2->addWidget(productAdd);

    productDelete = new QPushButton(horizontalLayoutWidget);
    productDelete->setObjectName(QStringLiteral("productDelete"));
    productDelete->setEnabled(false);
    productDelete->setIcon(icon1);

    horizontalLayout_2->addWidget(productDelete);


    verticalLayout_2->addLayout(horizontalLayout_2);


    horizontalLayout->addLayout(verticalLayout_2);

    categoryAdd->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
    categoryDelete->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
    productAdd->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
    productDelete->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));

    connect(categoryAdd, SIGNAL(clicked(bool)), this, SLOT(insertRowToTreeModel(bool)));
    connect(categoryDelete, SIGNAL(clicked(bool)), this, SLOT(removeRowFromTreeModel(bool)));

    connect(productAdd, SIGNAL(clicked(bool)), this, SLOT(insertProductToTable(bool)));
    connect(productDelete, SIGNAL(clicked(bool)), this, SLOT(removeProductFromTable(bool)));
}

void MainWindow::openReference(bool ac)
{
    referenceIndex = ui->tabWidget->addTab(horizontalLayoutWidget, "Справочник");
    ui->tabWidget->setCurrentIndex(referenceIndex);
}

void MainWindow::closeReference(bool ac)
{
    ui->tabWidget->removeTab(referenceIndex);
}

void MainWindow::selection(QItemSelection selected, QItemSelection deselected)
{
    QModelIndexList indexes = selected.indexes();
    if(indexes.size() > 0) {
        QModelIndex temp = indexes.first();
        selected.removeFirst();
        TreeItem* treeTemp = static_cast<TreeItem*>(temp.internalPointer());
        tableModel->clear();
        setTableModelData(treeTemp->getId());
    }
    this->categoryAdd->setEnabled(true);
    this->categoryDelete->setEnabled(true);
}

void MainWindow::selectionTable(QItemSelection selected, QItemSelection deselected)
{
    this->productAdd->setEnabled(true);
    this->productDelete->setEnabled(true);
}

void MainWindow::setTableModelData(int id)
{
    QSqlQuery category_products_statement(db->db);
    category_products_statement.prepare(treeModel->category_products_query);
    category_products_statement.bindValue(0, id);
    category_products_statement.exec();
    while(category_products_statement.next())
    {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(category_products_statement.value(3).toString()));
        items.append(new QStandardItem(category_products_statement.value(5).toString()));
        tableModel->appendRow(items);
    }
}

void MainWindow::insertRowToTreeModel(bool)
{
    TreeItem *item = static_cast<TreeItem *>(treeView->currentIndex().internalPointer());
    treeModel->insertRows(0,1, QModelIndex());
}

void MainWindow::removeRowFromTreeModel(bool)
{
    QModelIndex currentIndex = treeView->currentIndex();
    TreeItem *childItem = static_cast<TreeItem*>(currentIndex.internalPointer());
    QModelIndex parentIndex = currentIndex.parent();
    treeModel->removeRows(currentIndex.row(), 1, parentIndex);
}

void MainWindow::insertProductToTable(bool)
{
    tableModel->insertRow(0);
}

void MainWindow::removeProductFromTable(bool)
{
    QModelIndex currentIndex = tableView->currentIndex();
    tableModel->removeRow(currentIndex.row());
}
