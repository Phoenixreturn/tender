#include "pgvalidator.h"
#include "QMessageBox"

PGValidator::PGValidator(QObject *parent)
    : QValidator(parent)
{
    db = &Database::Instance();
    statements = &SqlStatements::Instance();
    if(!db->db.isOpen()) {
        db->connectToDataBase();
    }
    setData();
}

QValidator::State PGValidator::validate(QString &str, int &length) const
{
    if(values.contains(str)) {
        QMessageBox *msgBox = new QMessageBox();
        msgBox->setText("Внимание");
        msgBox->setInformativeText(QString("Данное наименование уже содержится в БД: %1").arg(str));
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->setDefaultButton(QMessageBox::Ok);
        msgBox->show();
        return QValidator::Invalid;
    }

    return QValidator::Acceptable;
}

void PGValidator::setData()
{
    QSqlQuery category_by_parent(db->db);
    category_by_parent.prepare(statements->all_products_query);
    category_by_parent.exec();
    int i = 0;
    while(category_by_parent.next())
    {
        values.insert(category_by_parent.value(1).toString());
        i++;
    }
}
