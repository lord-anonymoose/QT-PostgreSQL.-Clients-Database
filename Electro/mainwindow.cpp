#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::setWindowTitle("Electro Inc.");
    QPixmap myLogo("/Users/philipp/Desktop/Electro/logo.png");
    ui->ElectroLogo1->setPixmap(myLogo);
    ui->ElectroLogo1->setScaledContents( true );
    ui->ElectroLogo1->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->Password_lineEdit->setEchoMode(QLineEdit::Password);
    MainWindow::setWindowIcon(QIcon("/Users/philipp/Desktop/Electro/logo.icns"));
    myResources = new resources;
}

MainWindow::~MainWindow()
{
    delete ui;
    login = "";
    password = "";
}


void MainWindow::on_pushButton_clicked()
{
    login = ui->Login_lineEdit->text();
    password = ui->Password_lineEdit->text();
    ElectroDB = QSqlDatabase::addDatabase("QPSQL");
    ElectroDB.setHostName("localhost");
    ElectroDB.setDatabaseName("Electro");
    ElectroDB.setUserName(login);
    ElectroDB.setPassword(password);
    bool checker = ElectroDB.open();
    if (checker)
    {
        myElectro = new Electro();
        myElectro->show();
        this->close();
    }
    else
        QMessageBox::about(this, "Error", ";*( Oops... Something went wrong!");
    ui->Login_lineEdit->setText("");
    ui->Password_lineEdit->setText("");
}

void MainWindow::on_pushButton_2_clicked()
{
    myResources->show();
}
