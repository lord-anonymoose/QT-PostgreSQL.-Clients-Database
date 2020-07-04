#ifndef COUNTER_H
#define COUNTER_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSystemTrayIcon>


namespace Ui {
class method;
}

class method : public QDialog
{
    Q_OBJECT

public:
    explicit method(QWidget *parent = nullptr);
    ~method();

private:
    Ui::method *ui;
    QSqlDatabase ElectroDB;

};

#endif // COUNTER_H
