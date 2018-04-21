#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    treeModel = new TreeModel();
    ui->setupUi(this);
    ui->treeView->setModel(treeModel);

}

MainWindow::~MainWindow()
{
    delete ui;
}
