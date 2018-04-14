#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QtSql>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qDebug() << MAXBUFFERSIZE;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "mydb");
    db.setHostName("176.57.216.145");
    db.setDatabaseName("cl132598_tender");
    db.setUserName("cl132598_tender");
    db.setPassword("t8b54g2rg");
    bool ok = db.open();

    qDebug() << ok;

    return a.exec();
}
