#ifndef PGVALIDATOR_H
#define PGVALIDATOR_H

#include <QValidator>
#include "database.h"
#include "sqlstatements.h"

class PGValidator : public QValidator
{
    Q_OBJECT
public:
    explicit PGValidator(QObject * parent = Q_NULLPTR);
    virtual State validate(QString &, int &) const;
private:
    Database* db;
    SqlStatements* statements;
    QSet<QString> values;
    void setData();
};

#endif // PGVALIDATOR_H
