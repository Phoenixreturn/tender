#ifndef CUSTOMCOMBOBOX_H
#define CUSTOMCOMBOBOX_H

#include <QComboBox>
#include <QTreeView>

class CustomCombobox: public QComboBox
{
    Q_OBJECT
public:
    explicit CustomCombobox(QWidget *parent = 0);
    ~CustomCombobox();
protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void hidePopup();
protected:
    bool skipNextHide;
};

#endif // CUSTOMCOMBOBOX_H
