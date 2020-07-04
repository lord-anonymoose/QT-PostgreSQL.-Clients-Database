#ifndef ELECTRO_H
#define ELECTRO_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <branch.h>
#include <customer.h>
#include <payment.h>
#include <invoice.h>
#include <QSystemTrayIcon>
#include <reportplus.h>

namespace Ui {
class Electro;
}

class Electro : public QDialog
{
    Q_OBJECT
public slots:
public:
    explicit Electro();
    ~Electro();

private slots:
    void on_showBranches_clicked();

    void on_showCustomers_clicked();

    void on_showInvoices_clicked();

    void on_addButton_clicked();

    void on_editButton_clicked();

    void on_deleteButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_reportButtone_clicked();

    void on_showMethods_clicked();

    void on_pushButton_clicked();

private:
    Ui::Electro *ui;
    QSqlDatabase ElectroDB;
    QSqlTableModel* branches;
    QSqlTableModel* customers;
    QSqlTableModel* invoices;
    QSqlTableModel* methods;
    QSqlTableModel* logs;
    branch* myBranch;
    customer* myCustomer;
    invoice* myInvoice;
    payment* myPayment;

    QString chosenTable;
    QSystemTrayIcon* trayIcon;

    QSqlQueryModel* comboBoxModel;
    QSqlQueryModel* myView;
    reportPlus* report;
};

#endif // ELECTRO_H
