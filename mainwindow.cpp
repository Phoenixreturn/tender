#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProgressBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);   
    progressBar = createProgressBar();
    referenceWidget = new ReferenceWidget();
    ui->statusBar->addPermanentWidget(progressBar);
    addToolBar(Qt::TopToolBarArea, createToolbar());    

    connect(ui->openReference,SIGNAL(triggered(bool)),this, SLOT(openReference(bool)));
    connect(ui->closeReference,SIGNAL(triggered(bool)),this, SLOT(closeReference(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete progressBar;
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

QProgressBar *MainWindow::createProgressBar()
{
    QProgressBar* progressBar = new QProgressBar();
    progressBar->setAlignment(Qt::AlignRight);
    progressBar->setMaximumSize(90, 12);
    progressBar->setValue(50);
    progressBar->setMaximum(100);
    progressBar->setVisible(false);
}

void MainWindow::openReference(bool clicked)
{
    progressBar->show();
    referenceIndex = ui->tabWidget->addTab(referenceWidget, "Справочник");
    ui->tabWidget->setCurrentIndex(referenceIndex);

}

void MainWindow::closeReference(bool clicked)
{
    ui->tabWidget->removeTab(referenceIndex);
}

void MainWindow::update()
{

}
