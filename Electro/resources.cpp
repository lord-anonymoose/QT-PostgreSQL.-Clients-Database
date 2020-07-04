#include "resources.h"
#include "ui_resources.h"

resources::resources(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resources)
{
    ui->setupUi(this);
    resources::setWindowTitle("Resources");
    QPixmap Postgres("/Users/philipp/Desktop/Electro/Images/Postgres.png");
    ui->label->setPixmap(Postgres);
    ui->label->setScaledContents( true );
    ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    QPixmap TablePlus("/Users/philipp/Desktop/Electro/Images/TablePlus.png");
    ui->label_2->setPixmap(TablePlus);
    ui->label_2->setScaledContents( true );
    ui->label_2->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    QPixmap QTCreator("/Users/philipp/Desktop/Electro/Images/qt.png");
    ui->label_3->setPixmap(QTCreator);
    ui->label_3->setScaledContents( true );
    ui->label_3->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

}

resources::~resources()
{
    delete ui;
}
