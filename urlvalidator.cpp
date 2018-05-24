#include "urlvalidator.h"
#include <QRegExp>
#include <QMessageBox>

UrlValidator::UrlValidator(QObject *parent)
    : QValidator(parent)
{

}

QValidator::State UrlValidator::validate(QString &str, int &length) const
{
    QRegExp reg(PATTERN);
    bool regExMatch = false;
    reg.setCaseSensitivity(Qt::CaseInsensitive);
    reg.setPatternSyntax(QRegExp::RegExp);
    int id = reg.indexIn(str);

    if(id == 0)
        regExMatch = true;

    if(!regExMatch && length > 0) {
        QMessageBox *msgBox = new QMessageBox();
        msgBox->setText("Внимание");
        msgBox->setInformativeText(QString("Неверная ссылка: %1").arg(str));
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->setDefaultButton(QMessageBox::Ok);
        msgBox->show();
        return QValidator::Invalid;
    }

    return QValidator::Acceptable;
}
