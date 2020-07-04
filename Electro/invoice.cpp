#include "invoice.h"
#include "ui_invoice.h"
#include <QSqlDatabase>
#include <QSql>
#include <QMessageBox>
invoice::invoice(int current, bool isEditing) :
    ui(new Ui::invoice)
{
    ui->setupUi(this);
    invoice::setWindowTitle("Invoices");
    QSqlDatabase ElectroDB = QSqlDatabase::database("ElectroDB");

    customers = new QSqlQueryModel;
    QSqlQuery get_customers = QSqlQuery(ElectroDB);
    get_customers.prepare("SELECT customer_name FROM customers");
    get_customers.exec();
    customers->setQuery(get_customers);
    ui->customerComboBox->setModel(customers);

    methods = new QSqlQueryModel;
    QSqlQuery get_methods = QSqlQuery(ElectroDB);
    get_methods.prepare("SELECT method_name FROM methods");
    get_methods.exec();
    methods->setQuery(get_methods);
    ui->methodCombobox->setModel(methods);

    branches = new QSqlQueryModel;
    QSqlQuery get_branches = QSqlQuery(ElectroDB);
    get_branches.prepare("SELECT branch_name FROM branches");
    get_branches.exec();
    branches->setQuery(get_branches);
    ui->branchComboBox->setModel(branches);

    Editing = isEditing;
    currentID = current;
    QSqlQuery thisQuery = QSqlQuery(ElectroDB);
}

invoice::~invoice()
{
    delete ui;
}

void invoice::on_pushButton_clicked()
{
    if (Editing)
    {
        QSqlQuery thisQuery = QSqlQuery(ElectroDB);
        thisQuery.prepare("SELECT * from change_invoice(:_id, :_newamount, :_newdate, :_newcustomer, :_newbranch, :_newmethod);");
        thisQuery.bindValue(":_id", currentID);
        thisQuery.bindValue(":_newamount", ui->amountEdit->text());
        thisQuery.bindValue(":_newdate", ui->lineEdit->text());
        thisQuery.bindValue(":_newcustomer", ui->customerComboBox->currentText());
        thisQuery.bindValue(":_newbranch", ui->branchComboBox->currentText());
        thisQuery.bindValue(":_newmethod", ui->methodCombobox->currentText());
        bool checker = thisQuery.exec();
        if (checker)
        {
            QMessageBox::about(this,"Great!", "Invoice changed!");
        }
        if (!checker)
            QMessageBox::about(this,"Error!", "Something went wrong!");
    }

    if (!Editing)
    {
        QSqlQuery thisQuery = QSqlQuery(ElectroDB);
        thisQuery.prepare("SELECT * from add_invoice_beta(:_newamount, :_newdate, :_newcustomer, :_newbranch, :_newmethod);");
        thisQuery.bindValue(":_newamount", ui->amountEdit->text());
        thisQuery.bindValue(":_newdate", ui->lineEdit->text());
        thisQuery.bindValue(":_newcustomer", ui->customerComboBox->currentText());
        thisQuery.bindValue(":_newbranch", ui->branchComboBox->currentText());
        thisQuery.bindValue(":_newmethod", ui->methodCombobox->currentText());
        bool checker = thisQuery.exec();
        if (checker)
        {
            QMessageBox::about(this,"Great!", "New invoice!");
        }
        if (!checker)
            QMessageBox::about(this,"Error!", "Something went wrong!");
    }
}
