#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QSql>
#include <QFile>
#include "database.h"

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


    Database &db = Database::Instance();
    bool ok = db.connectToDataBase();
    Database::Instance();

    qDebug() << ok;
    QSqlQuery *query = new QSqlQuery(db.db);
    query->exec("SELECT * FROM categories");

    while (query->next()) {
           QString category = query->value(1).toString();
           qDebug() << category;
    }


    return a.exec();
}
