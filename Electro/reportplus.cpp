#include "reportplus.h"
#include "ui_reportplus.h"
#include <QComboBox>
#include <QMessageBox>
reportPlus::reportPlus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reportPlus)
{
    ui->setupUi(this);
    reportPlus::setWindowTitle("Report+");
    QPixmap myLogo("/Users/philipp/Desktop/Electro/logo.png");
    ui->logo->setPixmap(myLogo);
    ui->logo->setScaledContents( true );
    ui->logo->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    items << tr("") <<tr("Show branch clients:") << tr("Work") << tr("Other");

    QSqlDatabase ElectroDB = QSqlDatabase::database("ElectroDB");
    reportMode = 0;


}

reportPlus::~reportPlus()
{
    delete ui;
}


void reportPlus::on_pushButton_clicked()
{
    QSqlQueryModel *myModel = new QSqlQueryModel;
    myModel->setQuery("SELECT branch_name,"
                      "SUM ("
                          "CASE"
                          " WHEN invoice_branch = 3 THEN "
                              "1"
                          " ELSE "
                              "0"
                          " END "
                      ") AS branch_invoices "

                  " FROM "
                      "branches, invoices"
                  " WHERE "
                      "invoice_branch = branch_id AND branch_id = 3"
                  " GROUP BY branch_name;"
);
    QTableView *tv = new QTableView(this);
    tv->setModel(myModel);
    ui->tableView->setModel(myModel);
}

void reportPlus::on_pushButton_2_clicked()
{
    QSqlQueryModel *myModel = new QSqlQueryModel;
    myModel->setQuery("SELECT * FROM branch_invoices"
                      " ORDER BY quantity"
);
    QTableView *tv = new QTableView(this);
    tv->setModel(myModel);
    ui->tableView->setModel(myModel);

}

void reportPlus::on_pushButton_3_clicked()
{

    QSqlQueryModel *myModel = new QSqlQueryModel;
    myModel->setQuery("SELECT invoice_id, invoice_amount,"
                      " (SELECT customer_name FROM customers "
                          " WHERE customer_id = invoice_customer), "
                      " (SELECT METHOD_name FROM methods "
                          " WHERE method_id = invoice_method) "
                      " FROM (SELECT * FROM invoices WHERE invoice_method != 0) AS needed_methods "
                          " WHERE invoice_amount > (SELECT sum(invoice_amount)/count(invoice_amount) FROM invoices);"
);
    QTableView *tv = new QTableView(this);
    tv->setModel(myModel);
    ui->tableView->setModel(myModel);

}

void reportPlus::on_pushButton_4_clicked()
{
    QSqlQueryModel *myModel = new QSqlQueryModel;
    myModel->setQuery("SELECT invoice_branch, max(invoice_amount), branch_name "
                      " FROM invoices, branches "
                      " WHERE branch_id = invoice_branch "
                      " GROUP BY invoice_branch, branch_name "
                      " HAVING (max(invoice_amount)>='50');"

);
    QTableView *tv = new QTableView(this);
    tv->setModel(myModel);
    ui->tableView->setModel(myModel);

}

void reportPlus::on_pushButton_5_clicked()
{
    QSqlQueryModel *myModel = new QSqlQueryModel;
    myModel->setQuery("SELECT "
                      " invoice_amount, invoice_date "
                  " FROM "
                      " invoices "
                  " WHERE invoice_branch = ANY "
                      " (SELECT branch_id FROM branches WHERE branch_city = 'Cupertino')"
);
    QTableView *tv = new QTableView(this);
    tv->setModel(myModel);
    ui->tableView->setModel(myModel);

}

void reportPlus::on_pushButton_6_clicked()
{
    QSqlQueryModel *myModel = new QSqlQueryModel;
    myModel->setQuery("SELECT * "
                      " FROM invoices "
                      " WHERE invoice_amount > (SELECT sum(invoice_amount)/count(invoice_amount) FROM invoices);"
);
    QTableView *tv = new QTableView(this);
    tv->setModel(myModel);
    ui->tableView->setModel(myModel);

}

void reportPlus::on_pushButton_7_clicked()
{
    QSqlQueryModel *myModel = new QSqlQueryModel;
    myModel->setQuery("SELECT invoice_amount, invoice_date "
                      " FROM invoices "
                      " WHERE invoice_amount > (SELECT sum(invoice_amount)/count(invoice_amount) FROM invoices, branches WHERE invoice_branch = branch_id);"
);
    QTableView *tv = new QTableView(this);
    tv->setModel(myModel);
    ui->tableView->setModel(myModel);

}

void reportPlus::on_pushButton_8_clicked()
{
    QSqlQueryModel *myModel = new QSqlQueryModel;
    myModel->setQuery("SELECT (SELECT branch_id FROM branches WHERE branch_id = 3) "
                      " invoice_id, invoice_amount "
                   " FROM invoices WHERE invoice_branch = 3;"
);
    QTableView *tv = new QTableView(this);
    tv->setModel(myModel);
    ui->tableView->setModel(myModel);
}

void reportPlus::on_pushButton_9_clicked()
{
    QSqlQueryModel *myModel = new QSqlQueryModel;
    myModel->setQuery("SELECT customer_id, customer_name, customer_phone, "
                      " (SELECT COUNT(*) FROM invoices WHERE invoice_customer = customer_id) AS invoices "
                      " FROM customers;"
);
    QTableView *tv = new QTableView(this);
    tv->setModel(myModel);
    ui->tableView->setModel(myModel);

}

void reportPlus::on_pushButton_10_clicked()
{
    QSqlQueryModel *myModel = new QSqlQueryModel;
    myModel->setQuery("SELECT * FROM invoices "
                      " WHERE invoice_amount > (SELECT SUM(invoice_amount)/COUNT(invoice_amount) FROM invoices) "
);
    QTableView *tv = new QTableView(this);
    tv->setModel(myModel);
    ui->tableView->setModel(myModel);

}

void reportPlus::on_pushButton_11_clicked()
{
    QSqlQueryModel *myModel = new QSqlQueryModel;
    myModel->setQuery("SELECT invoice_amount "
                      " FROM invoices WHERE invoice_branch = (select branch_ID from branches where branches.branch_ID = invoices.invoice_branch)"
);
    QTableView *tv = new QTableView(this);
    tv->setModel(myModel);
    ui->tableView->setModel(myModel);
}
