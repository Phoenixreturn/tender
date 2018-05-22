#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include "customcombobox.h"
#include "referencewidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void slotNoImpl() {}
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int referenceIndex;
    ReferenceWidget* referenceWidget;
    QToolBar* createToolbar();
private slots:
    void openReference(bool clicked);
    void closeReference(bool clicked);
    void update();
};

#endif // MAINWINDOW_H
