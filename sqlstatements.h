#ifndef SQLSTATEMENTS_H
#define SQLSTATEMENTS_H

#include <QObject>
#include "database.h"

class SqlStatements : public QObject
{
    Q_OBJECT
public:
    QString category_by_parent_query;
    QString category_products_query;
    QString add_category_query;
    QString add_product_query;
    QString delete_category_query;
    QString delete_product_query;
    QString update_category_query;
    QString update_product_query;
    QString update_mapping_query;
    QString remove_mapping_query;
    QString contains_in_mapping_query;
    QString delete_in_mapping_query;
    QString delete_in_mapping_category_query;
    QString contains_category_in_mapping_query;
    QString contains_product_in_mapping_query;
    QString all_products_query;

    static SqlStatements& Instance();
private:
     SqlStatements(QObject* parent = 0);
     ~SqlStatements();

     SqlStatements(SqlStatements const&);
     SqlStatements& operator= (SqlStatements const&);

     Database* db;
     int readSqlStatements();
};

#endif // SQLSTATEMENTS_H
