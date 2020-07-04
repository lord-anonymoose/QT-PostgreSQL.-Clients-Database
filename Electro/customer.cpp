#include "customer.h"
#include "ui_customer.h"
#include <QMessageBox>


customer::customer(QString tax, bool isEditing) :
    ui(new Ui::customer)
{
    ui->setupUi(this);
    customer::setWindowTitle("Customer");
    ui->tax_LineEdit->setText(tax);
    Editing = isEditing;
    oldTax = tax;

    if (Editing)
    {
        QSqlQuery thisQuery = QSqlQuery(ElectroDB);
        thisQuery.prepare("SELECT customer_name from customers WHERE customer_tax = :_currentTax");
        thisQuery.bindValue(":_currentTax", oldTax);
        thisQuery.exec();
        thisQuery.first();
        ui->name_LineEdit->setText(thisQuery.value(0).toString());

        thisQuery = QSqlQuery(ElectroDB);
        thisQuery.prepare("SELECT customer_phone from customers WHERE customer_tax = :_currentTax");
        thisQuery.bindValue(":_currentTax", oldTax);
        thisQuery.exec();
        thisQuery.first();
        ui->phone_LineEdit->setText(thisQuery.value(0).toString());

        thisQuery = QSqlQuery(ElectroDB);
        thisQuery.prepare("SELECT customer_address from customers WHERE customer_tax = :_currentTax");
        thisQuery.bindValue(":_currentTax", oldTax);
        thisQuery.exec();
        thisQuery.first();
        ui->address_LineEdit->setText(thisQuery.value(0).toString());

    }

}

customer::~customer()
{
    delete ui;
}

void customer::on_saveButton_clicked()
{
    bool checker = true;

    if (ui->name_LineEdit->text() == "")
    {
        checker = false;
        QMessageBox::about(this,"Error!", "No city data provided!");
    }
    if (ui->tax_LineEdit->text() == "")
    {
        checker = false;
        QMessageBox::about(this,"Error!", "No name provided!");
    }
    if (ui->phone_LineEdit->text() == "")
    {
        checker = false;
        QMessageBox::about(this,"Error!", "No manager provided!");
    }
    if (ui->phone_LineEdit->text() == "")
    {
        checker = false;
        QMessageBox::about(this,"Error!", "No manager provided!");
    }

    QSqlDatabase ElectroDB = QSqlDatabase::database("ElectroDB");

    if (checker == true)
    {
        QSqlQuery myQuery = QSqlQuery(ElectroDB);
        if (!Editing)
        {
            myQuery.prepare("SELECT * FROM add_customer(:_name, :_tax, :_phone, :_address)");
            myQuery.bindValue(":_name", ui->name_LineEdit->text());
            myQuery.bindValue(":_tax", ui->tax_LineEdit->text());
            myQuery.bindValue(":_phone", ui->phone_LineEdit->text());
            myQuery.bindValue(":_address", ui->address_LineEdit->text());
            checker = myQuery.exec();
            if (checker)
            {
                QMessageBox::about(this,"Welcome!", "New customer!");
                ui->name_LineEdit->setText("");
                ui->tax_LineEdit->setText("");
                ui->phone_LineEdit->setText("");
                ui->address_LineEdit->setText("");
            }
            if (!checker)
                QMessageBox::about(this,"Error!", "Something went wrong!");
        }
        else
        {
            myQuery.prepare("SELECT * FROM change_customer(:_oldtax, :_newname, :_newtax, :_newphone, :_newaddress)");
            myQuery.bindValue(":_oldtax", oldTax);
            myQuery.bindValue(":_newname", ui->name_LineEdit->text());
            myQuery.bindValue(":_newtax", ui->tax_LineEdit->text());
            myQuery.bindValue(":_newphone", ui->phone_LineEdit->text());
            myQuery.bindValue(":_newaddress", ui->address_LineEdit->text());
            checker = myQuery.exec();
            if (checker)
            {
                trayIcon = new QSystemTrayIcon(this);
                trayIcon->setVisible(true);
                trayIcon->showMessage("Well done!", "Customer have been updated");
                ui->name_LineEdit->setText("");
                ui->tax_LineEdit->setText("");
                ui->phone_LineEdit->setText("");
                ui->address_LineEdit->setText("");
            }
            if (!checker)
                QMessageBox::about(this,"Error!", "Something went wrong!");
        }
    }
}
