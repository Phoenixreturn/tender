#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>

#define HOST_NAME "176.57.216.145"
#define DATABASE_NAME "cl132598_tender"
#define USER_NAME "cl132598_tender"
#define PASSWORD "t8b54g2rg"

class Database
{
public:
    QSqlDatabase db;
    static Database& Instance();
    bool connectToDataBase();
private:
    Database();
    ~Database();

    Database(Database const&);
    Database& operator= (Database const&);
};

#endif // DATABASE_H
