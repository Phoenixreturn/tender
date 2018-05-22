#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProgressBar>
#include <QProgressDialog>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);   
    referenceWidget = new ReferenceWidget();
    addToolBar(Qt::TopToolBarArea, createToolbar());    

    connect(ui->openReference,SIGNAL(triggered(bool)),this, SLOT(openReference(bool)));
    connect(ui->closeReference,SIGNAL(triggered(bool)),this, SLOT(closeReference(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete referenceWidget;
}

QToolBar *MainWindow::createToolbar()
{
   QToolBar* ptb = new QToolBar("Linker ToolBar");
   ptb->setMovable(false);

   ptb->addAction(QIcon(":/icons/open.png"), "1", this, SLOT(slotNoImpl()));
   ptb->addSeparator();
   ptb->addAction(QIcon(":/icons/save.png"), "2", this, SLOT(update()));
   ptb->addAction(QIcon(":/icons/refresh.png"), "3", this, SLOT(slotNoImpl()));
   ptb->addSeparator();

   return ptb;
}

void MainWindow::openReference(bool clicked)
{
    referenceIndex = ui->tabWidget->addTab(referenceWidget, "Справочник");
    ui->tabWidget->setCurrentIndex(referenceIndex);
}

void MainWindow::closeReference(bool clicked)
{
    ui->tabWidget->removeTab(referenceIndex);
}

void MainWindow::update()
{
    QProgressDialog* pprd = new QProgressDialog("Сохранить данные...", "&Отмена", 0, 0);
    pprd->setRange(0,0);
    pprd->setValue(0);
    pprd->setModal(true);
    pprd->show();
    QFuture <void> future = QtConcurrent::run(referenceWidget, &ReferenceWidget::updateModels);
    while(future.isRunning()) {
        qApp->processEvents();
    }
    delete pprd;
}
