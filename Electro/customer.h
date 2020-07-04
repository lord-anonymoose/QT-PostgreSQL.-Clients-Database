#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QDialog>
#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QString>
#include <QSqlQuery>
#include <QSystemTrayIcon>

namespace Ui {
class customer;
}

class customer : public QDialog
{
    Q_OBJECT

public:
    explicit customer(QString tax,bool isEditing);
    ~customer();

private slots:
    void on_saveButton_clicked();

private:
    Ui::customer *ui;
    QSqlDatabase ElectroDB;
    bool Editing;
    QString oldTax;
    QSystemTrayIcon* trayIcon;


};

#endif // CUSTOMER_H
