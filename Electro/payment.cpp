#include "payment.h"
#include "ui_payment.h"
#include <QSql>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QString>
#include <QSystemTrayIcon>
#include <QSqlQuery>
#include <QMessageBox>

payment::payment(QString name, bool isEditing) :
    ui(new Ui::payment)
{
    ui->setupUi(this);
    payment::setWindowTitle("Payment methods");
    ui->name_LineEdit->setText(name);
    oldName = name;
    Editing = isEditing;
    QSqlDatabase ElectroDB = QSqlDatabase::database("ElectroDB");

    if (Editing)
    {
        QSqlQuery thisQuery = QSqlQuery(ElectroDB);
        thisQuery.prepare("SELECT method_fee from methods WHERE method_name = :_currentName");
        thisQuery.bindValue(":_currentName", oldName);
        thisQuery.exec();
        thisQuery.first();
        ui->amount_LineEdit->setText(thisQuery.value(0).toString());
    }
    else
        ui->amount_LineEdit->setText("");
}

payment::~payment()
{
    delete ui;
}

void payment::on_saveButton_clicked()
{
    QSqlQuery myQuery = QSqlQuery(ElectroDB);
    bool checker = true;
    if (Editing)
    {
        myQuery.prepare("SELECT * FROM change_method(:_oldname, :_newname, :_fee)");
        myQuery.bindValue(":_oldname", oldName);
        myQuery.bindValue(":_newname", ui->name_LineEdit->text());
        myQuery.bindValue(":_fee", ui->amount_LineEdit->text());
        checker = myQuery.exec();
        if (checker)
        {
            QMessageBox::about(this,"Welcome!", "New branch!");
            ui->name_LineEdit->setText("");
            ui->amount_LineEdit->setText("");
        }
        if (!checker)
            QMessageBox::about(this,"Error!", "Something went wrong!" + oldName);

    }
    else
    {
        myQuery.prepare("SELECT * FROM add_method(:_name, :_fee)");
        myQuery.bindValue(":_name", ui->name_LineEdit->text());
        myQuery.bindValue(":_fee", ui->amount_LineEdit->text());
        checker = myQuery.exec();
        if (checker)
        {
            QMessageBox::about(this,"Welcome!", "New branch!");
            ui->name_LineEdit->setText("");
            ui->amount_LineEdit->setText("");
        }
        if (!checker)
            QMessageBox::about(this,"Error!", "Something went wrong!");

    }

}
