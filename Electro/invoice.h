#ifndef INVOICE_H
#define INVOICE_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
class invoice;
}

class invoice : public QDialog
{
    Q_OBJECT

public:
    explicit invoice(int current, bool isEditing);
    ~invoice();

private slots:
    void on_pushButton_clicked();

private:
    Ui::invoice *ui;
    QSqlQueryModel* customers;
    QSqlQueryModel* branches;
    QSqlQueryModel* methods;
    bool Editing;
    QSqlDatabase ElectroDB;
    int currentID;
};

#endif // INVOICE_H
