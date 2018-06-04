#include "referencewidget.h"
#include "deselectabletreeview.h"
#include "referencewidget.h"
#include "urlitemdelegate.h"
#include <QHeaderView>

ReferenceWidget::ReferenceWidget()
{
    createButtons();
    createLayouts();
    setViewModels();
    setContextMenu();
    setItemDelegates();
    connectSlots();
    connect(categoryAdd, SIGNAL(clicked(bool)), this, SLOT(insertRowToTreeModel(bool)));
    connect(categoryDelete, SIGNAL(clicked(bool)), this, SLOT(removeRowFromTreeModel(bool)));
    connect(productAdd, SIGNAL(clicked(bool)), this, SLOT(insertProductToTable(bool)));
    connect(productDelete, SIGNAL(clicked(bool)), this, SLOT(removeProductFromTable(bool)));

}

ReferenceWidget::~ReferenceWidget()
{

}

void ReferenceWidget::createLayouts()
{
    horizontalLayout = new QHBoxLayout(this);
    verticalTreeLayout = new QVBoxLayout();
    treeView = new DeselectableTreeView(this);
    verticalTreeLayout->addWidget(treeView);
    horizontalLayout->addLayout(verticalTreeLayout, 1);
    verticalTableLayout = new QVBoxLayout();
    tableView = new QTableView(this);
    tableView->setMouseTracking(true);
    tableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    verticalTableLayout->addWidget(tableView);
    horizontalButtonTableLayout = new QHBoxLayout();
    verticalTableLayout->addLayout(horizontalButtonTableLayout);
    horizontalLayout->addLayout(verticalTableLayout, 2);
    verticalTreeLayout->addWidget(categoryAdd);
    verticalTreeLayout->addWidget(categoryDelete);
    horizontalButtonTableLayout->addWidget(productAdd);
    horizontalButtonTableLayout->addWidget(productDelete);
}

void ReferenceWidget::createButtons()
{
    QIcon addIcon;
    addIcon.addFile(QStringLiteral(":/icons/add_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    QIcon deleteIcon;
    deleteIcon.addFile(QStringLiteral(":/icons/delete_icon.png"), QSize(), QIcon::Normal, QIcon::Off);

    categoryAdd = new QPushButton(this);
    categoryDelete = new QPushButton(this);
    productAdd = new QPushButton(this);
    productDelete = new QPushButton(this);
    categoryAdd->setEnabled(true);
    categoryDelete->setEnabled(false);
    productAdd->setEnabled(false);
    productDelete->setEnabled(false);

    categoryAdd->setIcon(addIcon);
    categoryDelete->setIcon(deleteIcon);
    productAdd->setIcon(addIcon);
    productDelete->setIcon(deleteIcon);

    categoryAdd->setText("Добавить категорию");
    categoryDelete->setText("Удалить категорию");
    productAdd->setText("Добавить продукт");
    productDelete->setText("Удалить продукт");
}

void ReferenceWidget::setItemDelegates()
{
    PGQueryItemDelegate* pgquery = new PGQueryItemDelegate(tableView);
    UrlItemDelegate* urlDelegate = new UrlItemDelegate(tableView);
    tableView->setItemDelegateForColumn(4, urlDelegate);
    tableView->setItemDelegate(pgquery);
}

void ReferenceWidget::setViewModels()
{
    treeModel = new TreeModel();
    tableModel = new TableModel();
    treeView->setModel(treeModel);
    tableView->setModel(tableModel);
    selectionTreeModel = treeView->selectionModel();
    selectionTableModel = tableView->selectionModel();
}

void ReferenceWidget::updateModels()
{
    treeModel->updateModel();
    tableModel->updateModel();
}

void ReferenceWidget::refreshModels()
{
    treeView->setModel(NULL);
    tableView->setModel(NULL);
    delete treeModel;
    delete tableModel;
    setViewModels();
    connectSlots();
    this->productAdd->setEnabled(false);
    this->productDelete->setEnabled(false);
}

void ReferenceWidget::setContextMenu()
{
    treeView->setContextMenuPolicy(Qt::ActionsContextMenu);
    refContextMenu = new QMenu(treeView);
    sampleAction = new QAction("Sample Action", refContextMenu);
    treeView->addAction(sampleAction);
}

void ReferenceWidget::selectionTree(QItemSelection selected, QItemSelection deselected)
{
    QModelIndexList indexes = selected.indexes();
    if(indexes.size() > 0) {
        QModelIndex temp = indexes.first();
        GeneralItem* category = static_cast<GeneralItem*>(temp.internalPointer());
        selected.removeFirst();
        TableItem::setCategory(category);
        tableModel->setupModelData();
    }
    this->productAdd->setEnabled(true);
    this->categoryAdd->setEnabled(true);
    this->categoryDelete->setEnabled(true);
}

void ReferenceWidget::selectionTable(QItemSelection selected, QItemSelection deselected)
{
    this->productAdd->setEnabled(true);
    this->productDelete->setEnabled(true);
}

void ReferenceWidget::insertRowToTreeModel(bool)
{
    treeModel->insertRows(0,1, treeView->currentIndex());
}

void ReferenceWidget::removeRowFromTreeModel(bool)
{
    QModelIndex currentIndex = treeView->currentIndex();
    QModelIndex parentIndex = currentIndex.parent();
    tableModel->clear();
    treeModel->removeRows(currentIndex.row(), 1, parentIndex);
}

void ReferenceWidget::insertProductToTable(bool)
{
    tableModel->insertRow(0);
}

void ReferenceWidget::removeProductFromTable(bool)
{
    QMessageBox::StandardButton reply;
     reply = QMessageBox::question(this, "Подтвердить удаление", "Удалить?",
                                   QMessageBox::Yes|QMessageBox::No);
     if (reply == QMessageBox::Yes) {
         QModelIndex currentIndex = tableView->currentIndex();
         tableModel->removeRow(currentIndex.row());
     }
}

void ReferenceWidget::resizeToContentsTree(const QModelIndex &index)
{
    treeView->resizeColumnToContents(index.column());
}

void ReferenceWidget::connectSlots()
{
    connect(selectionTreeModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(selectionTree(QItemSelection,QItemSelection)));
    connect(selectionTableModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(selectionTable(QItemSelection,QItemSelection)));
    connect(treeView, SIGNAL(expanded(QModelIndex)), this, SLOT(resizeToContentsTree(QModelIndex)));
     connect(treeView, SIGNAL(collapsed(QModelIndex)), this, SLOT(resizeToContentsTree(QModelIndex)));
}
