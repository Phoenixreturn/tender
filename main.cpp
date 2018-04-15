#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QtSql>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QMap<QString,QString> queries;

    qDebug() << MAXBUFFERSIZE;

    QFile file(QUERIES);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;

    while (!file.atEnd()) {
        const QByteArray line = file.readLine();
        const QString str( line );
        const QStringList lst = str.split('=');
        if (lst.size() != 2) {
            qDebug() << "error";
            return -2;
        }
        queries.insert(lst.first(), lst.last() );
        qDebug() << QString("%1,%2").arg( lst.first() ).arg( lst.last() );
    }

    file.close();


    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "mydb");
    db.setHostName("176.57.216.145");
    db.setDatabaseName("cl132598_tender");
    db.setUserName("cl132598_tender");
    db.setPassword("t8b54g2rg");
    bool ok = db.open();

    QSqlQuery *query = new QSqlQuery(db);
    query->exec("SELECT * FROM categories");

    while (query->next()) {
           QString category = query->value(1).toString();
           qDebug() << category;
    }

    qDebug() << ok;

    return a.exec();
}
