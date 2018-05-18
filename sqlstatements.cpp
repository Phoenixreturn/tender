#include "sqlstatements.h"

SqlStatements &SqlStatements::Instance()
{
    static SqlStatements statements;
    return statements;
}

SqlStatements::SqlStatements(QObject *parent)
{
    db = &Database::Instance();
    if(!db->db.isOpen()) {
            db->connectToDataBase();
    }
    readSqlStatements();
}

SqlStatements::~SqlStatements()
{

}

int SqlStatements::readSqlStatements()
{
    QFile file(QUERIES);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;

    while (!file.atEnd()) {
        const QByteArray line = file.readLine();
        const QString str( line );
        const QStringList lst = str.split(QRegExp("=="));
        if(!QString::compare(lst.first(), "category_by_parent", Qt::CaseInsensitive)) {
             category_by_parent_query = lst.last();
        }
        if(!QString::compare(lst.first(), "category_products", Qt::CaseInsensitive)) {
             category_products_query = lst.last();
        }
        if(!QString::compare(lst.first(), "add_category", Qt::CaseInsensitive)) {
             add_category_query = lst.last();
        }
        if(!QString::compare(lst.first(), "add_product", Qt::CaseInsensitive)) {
             add_product_query = lst.last();
        }
        if(!QString::compare(lst.first(), "delete_category", Qt::CaseInsensitive)) {
             delete_category_query = lst.last();
        }
        if(!QString::compare(lst.first(), "delete_product", Qt::CaseInsensitive)) {
             delete_product_query = lst.last();
        }
        if(!QString::compare(lst.first(), "update_mapping", Qt::CaseInsensitive)) {
             update_mapping_query = lst.last();
        }
        if(!QString::compare(lst.first(), "remove_mapping", Qt::CaseInsensitive)) {
             remove_mapping_query = lst.last();
        }
        if(!QString::compare(lst.first(), "containts_category_in_mapping", Qt::CaseInsensitive)) {
             contains_category_in_mapping_query = lst.last();
        }
        if(!QString::compare(lst.first(), "containts_product_in_mapping", Qt::CaseInsensitive)) {
             contains_product_in_mapping_query = lst.last();
        }
    }

    file.close();
    return 0;
}
