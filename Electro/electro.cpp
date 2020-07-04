#include "electro.h"
#include "ui_electro.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QShortcut>
#include <QSqlQuery>

Electro::Electro ():

    ui(new Ui::Electro)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    Electro::setWindowTitle("Electro");
    QPixmap myLogo("/Users/philipp/Desktop/Electro/logo.png");
    ui->ElectroLogo->setPixmap(myLogo);
    ui->ElectroLogo->setScaledContents( true );
    ui->ElectroLogo->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->tableView->verticalHeader()->hide();

    QSqlDatabase ElectroDB = QSqlDatabase::database("ElectroDB");
    myBranch = new branch ("", false);
    myCustomer = new customer ("", false);
    myInvoice = new invoice(0, false);
    myPayment = new payment("", false);
    chosenTable = "none";
    report = new reportPlus;
}

Electro::~Electro()
{
    delete ui;
    delete myBranch;
    delete myCustomer;
}

void Electro::on_showBranches_clicked()
{
    ui->comboBox->setCurrentIndex(0);
    branches = new QSqlTableModel(this,ElectroDB);
    branches->setTable("branches");
    branches->select();
    branches->setHeaderData(0, Qt::Horizontal, tr("ID"));
    branches->setHeaderData(1, Qt::Horizontal, tr("City"));
    branches->setHeaderData(2, Qt::Horizontal, tr("Name"));
    branches->setHeaderData(3, Qt::Horizontal, tr("Manager"));
    ui->tableView->setModel(branches);
    chosenTable = "branches";
    myCustomer->hide();
    myInvoice->hide();

    comboBoxModel = new QSqlQueryModel;
    QSqlQuery get_branches = QSqlQuery(ElectroDB);
    get_branches.prepare("SELECT branch_name FROM branches");
    get_branches.exec();
    comboBoxModel->setQuery(get_branches);
    ui->comboBox->setModel(comboBoxModel);
    ui->tableView->setColumnHidden(0, true);
}

void Electro::on_showCustomers_clicked()
{
    ui->comboBox->setCurrentIndex(0);
    customers = new QSqlTableModel(this,ElectroDB);
    customers->setTable("customers");
    customers->select();
    customers->setHeaderData(0, Qt::Horizontal, tr("ID"));
    customers->setHeaderData(1, Qt::Horizontal, tr("Name"));
    customers->setHeaderData(2, Qt::Horizontal, tr("Tax"));
    customers->setHeaderData(3, Qt::Horizontal, tr("Phone"));
    customers->setHeaderData(4, Qt::Horizontal, tr("Address"));
    ui->tableView->setModel(customers);
    chosenTable = "customers";
    myBranch->hide();
    myInvoice->hide();

    comboBoxModel = new QSqlQueryModel;
    QSqlQuery get_customers = QSqlQuery(ElectroDB);
    get_customers.prepare("SELECT customer_tax FROM customers");
    get_customers.exec();
    comboBoxModel->setQuery(get_customers);
    ui->comboBox->setModel(comboBoxModel);
}

void Electro::on_showInvoices_clicked()
{
    ui->comboBox->setCurrentIndex(0);
    myCustomer->hide();
    myInvoice->hide();
    myBranch->hide();

    invoices = new QSqlTableModel(this,ElectroDB);
    invoices->setTable("invoices");
    invoices->select();
    ui->tableView->setModel(invoices);
    chosenTable = "invoices";

    comboBoxModel = new QSqlQueryModel;
    QSqlQuery get_invoices = QSqlQuery(ElectroDB);
    get_invoices.prepare("SELECT invoice_id FROM invoices");
    get_invoices.exec();
    comboBoxModel->setQuery(get_invoices);
    ui->comboBox->setModel(comboBoxModel);
}

void Electro::on_showMethods_clicked()
{
    ui->comboBox->setCurrentIndex(0);
    methods = new QSqlTableModel(this,ElectroDB);
    methods->setTable("methods");
    methods->select();
    ui->tableView->setModel(methods);
    chosenTable = "methods";

    comboBoxModel = new QSqlQueryModel;
    QSqlQuery get_methods = QSqlQuery(ElectroDB);
    get_methods.prepare("SELECT method_name FROM methods");
    get_methods.exec();
    comboBoxModel->setQuery(get_methods);
    ui->comboBox->setModel(comboBoxModel);
}

void Electro::on_addButton_clicked()
{
    if (chosenTable == "none")
    {
        QMessageBox::about(this, "Error", "Choose table which you want to add to first!");
    }

    if (chosenTable == "branches")
    {
        delete myBranch;
        myBranch = new branch ("", false);
        myBranch->show();
    }

    if (chosenTable == "customers")
    {
        delete myCustomer;
        myCustomer = new customer ("", false);
        myCustomer->show();
    }

    if (chosenTable == "methods")
    {
        delete myPayment;
        myPayment = new payment ("", false);
        myPayment->show();
    }

    if (chosenTable == "invoices")
    {
        myInvoice->show();
    }
}


void Electro::on_editButton_clicked()
{
    if (chosenTable == "none")
    {
        QMessageBox::about(this, "Error", "Choose table which you want to edit first!");
    }

    if (chosenTable == "branches")
    {
        delete myBranch;
        myBranch = new branch (ui->comboBox->currentText(), true);
        myBranch->show();
    }

    if (chosenTable == "customers")
    {
        delete myCustomer;
        myCustomer = new customer (ui->comboBox->currentText(), true);
        myCustomer->show();
    }

    if (chosenTable == "invoices")
    {
        delete myInvoice;
        myInvoice = new invoice(ui->comboBox->currentText().toInt(), true);
        myInvoice->show();
    }

    if (chosenTable == "methods")
    {
        delete myPayment;
        myPayment = new payment (ui->comboBox->currentText(), true);
        myPayment->show();
    }
}


void Electro::on_deleteButton_clicked()
{
    QSqlQuery deleteQuery = QSqlQuery(ElectroDB);
    QString item = ui->comboBox->currentText();
    bool checker;
    if (chosenTable == "branches")
    {
        deleteQuery.prepare("SELECT * FROM public.delete_branch(:_name)");
        deleteQuery.bindValue(":_name", item);
        checker = deleteQuery.exec();
        if (!checker)
            QMessageBox::about(this,"Error", "Error! Branch " + item + " can not be deleted!");
        else
        {
            trayIcon = new QSystemTrayIcon(this);
            trayIcon->setVisible(true);
            trayIcon->showMessage("We will miss them!", "You succesfully deleted " +item + " branch.");
        }
    }
    else
    {
        if (chosenTable == "customers")
        {
            deleteQuery.prepare("SELECT * FROM public.delete_customer(:_tax)");
            deleteQuery.bindValue(":_tax", item);
            checker = deleteQuery.exec();
            if (!checker)
                QMessageBox::about(this,"Error", "Error! Customer " + item + " can not be deleted!");
            else
            {
                trayIcon = new QSystemTrayIcon(this);
                trayIcon->setVisible(true);
                trayIcon->showMessage("Hope to see them again!", "You succesfully deleted " +item);
            }
        }
    }
    if (chosenTable == "invoices")
    {
        deleteQuery.prepare("SELECT * FROM public.delete_invoice(:_id)");
        deleteQuery.bindValue(":_id", item.toInt());
        checker = deleteQuery.exec();
        if (!checker)
            QMessageBox::about(this,"Error", "Error!" + item + "Invoice can not be deleted!");
        else
        {
            trayIcon = new QSystemTrayIcon(this);
            trayIcon->setVisible(true);
            trayIcon->showMessage("Lost!", "The invoice has been deleted");
        }
    }

    if (chosenTable == "methods")
    {
        deleteQuery.prepare("SELECT * FROM public.delete_method(:_name)");
        deleteQuery.bindValue(":_name", item);
        checker = deleteQuery.exec();
        if (!checker)
            QMessageBox::about(this,"Error", "Error!" + item + " Method can not be deleted!");
        else
        {
            trayIcon = new QSystemTrayIcon(this);
            trayIcon->setVisible(true);
            trayIcon->showMessage("It's been great!", "The payment method has been deleted");
        }
    }
}

void Electro::on_tableView_doubleClicked(const QModelIndex &index)
{
    ui->comboBox->setCurrentIndex(index.row());
}

void Electro::on_reportButtone_clicked()
{
    report->hide();
    report->show();

}


void Electro::on_pushButton_clicked()
{
    logs = new QSqlTableModel(this,ElectroDB);
    logs->setTable("logs");
    logs->select();
    ui->tableView->setModel(logs);
    chosenTable = "logs";

    comboBoxModel = new QSqlQueryModel;
    ui->comboBox->setModel(comboBoxModel);
}
