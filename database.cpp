#include "database.h"

Database::Database()
{
    db = QSqlDatabase::addDatabase("QMYSQL", "mydb");
}

Database::~Database()
{

}

Database &Database::Instance()
{
    static Database db;
    return db;
}

bool Database::connectToDataBase()
{
    db.setHostName(HOST_NAME);
    db.setDatabaseName(DATABASE_NAME);
    db.setUserName(USER_NAME);
    db.setPassword(PASSWORD);
    db.setConnectOptions("MYSQL_OPT_RECONNECT=1");
    return db.open();
}
