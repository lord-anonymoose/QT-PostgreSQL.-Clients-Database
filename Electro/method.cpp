#include "method.h"
#include "ui_method.h"

method::method(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::method)
{
    ui->setupUi(this);
    QSqlDatabase ElectroDB = QSqlDatabase::database("ElectroDB");
}

method::~method()
{
    delete ui;
}
