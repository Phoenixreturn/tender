#ifndef URLVALIDATOR_H
#define URLVALIDATOR_H

#define PATTERN "^(https?:\/\/)(www\.)?([a-z0-9\.:].*)$"

#include <QValidator>

class UrlValidator : public QValidator
{
    Q_OBJECT
public:
    explicit UrlValidator(QObject * parent = Q_NULLPTR);

    virtual State validate(QString &, int &) const;
signals:
    void setError(const QString& msg) const;
};

#endif // URLVALIDATOR_H
