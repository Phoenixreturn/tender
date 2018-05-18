#include "referencewidget.h"
#include "deselectabletreeview.h"

ReferenceWidget::ReferenceWidget()
{
    createButtons();
    createLayouts();
    setViewModels();
    setContextMenu();
    setItemDelegates();

    connect(selectionTreeModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(selectionTree(QItemSelection,QItemSelection)));
    connect(selectionTableModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(selectionTable(QItemSelection,QItemSelection)));

    connect(categoryAdd, SIGNAL(clicked(bool)), this, SLOT(insertRowToTreeModel(bool)));
    connect(categoryDelete, SIGNAL(clicked(bool)), this, SLOT(removeRowFromTreeModel(bool)));
    connect(productAdd, SIGNAL(clicked(bool)), this, SLOT(insertProductToTable(bool)));
    connect(productDelete, SIGNAL(clicked(bool)), this, SLOT(removeProductFromTable(bool)));

}

void ReferenceWidget::createLayouts()
{
    horizontalLayout = new QHBoxLayout(this);
    verticalTreeLayout = new QVBoxLayout();
    treeView = new DeselectableTreeView(this);
    treeView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    verticalTreeLayout->addWidget(treeView);
    horizontalLayout->addLayout(verticalTreeLayout);
    verticalTableLayout = new QVBoxLayout();
    tableView = new QTableView(this);
    tableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    verticalTableLayout->addWidget(tableView);
    horizontalButtonTableLayout = new QHBoxLayout();
    verticalTableLayout->addLayout(horizontalButtonTableLayout);
    horizontalLayout->addLayout(verticalTableLayout);
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
        selected.removeFirst();
        GeneralItem* treeTemp = static_cast<GeneralItem*>(temp.internalPointer());
        tableModel->setCategoryId(treeTemp->getId());
        tableModel->setupModelData();
    }
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
