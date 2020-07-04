#include "branch.h"
#include "ui_branch.h"
#include <QSqlQuery>
#include <QMessageBox>

branch::branch(QString name, bool isEditing) :
    ui(new Ui::branch)
{
    ui->setupUi(this);
    branch::setWindowTitle("Branch");    
    ui->name_LineEdit->setText(name);
    oldName = name;
    Editing = isEditing;
    QSqlDatabase ElectroDB = QSqlDatabase::database("ElectroDB");

    if (Editing)
    {
        QSqlQuery thisQuery = QSqlQuery(ElectroDB);
        thisQuery.prepare("SELECT branch_city from branches WHERE branch_name = :_currentName");
        thisQuery.bindValue(":_currentName", oldName);
        thisQuery.exec();
        thisQuery.first();
        ui->city_LineEdit->setText(thisQuery.value(0).toString());

        thisQuery = QSqlQuery(ElectroDB);
        thisQuery.prepare("SELECT branch_manager from branches WHERE branch_name = :_currentName");
        thisQuery.bindValue(":_currentName", oldName);
        thisQuery.exec();
        thisQuery.first();
        ui->manager_LineEdit->setText(thisQuery.value(0).toString());
    }
}

branch::~branch()
{
    delete ui;
}

void branch::on_saveButton_clicked()
{
    QSqlQuery myQuery = QSqlQuery(ElectroDB);
    bool checker = true;

    if (ui->city_LineEdit->text() == "")
    {
        checker = false;
        QMessageBox::about(this,"Error!", "No city data provided!");
    }

    if (ui->name_LineEdit->text() == "")
    {
        checker = false;
        QMessageBox::about(this,"Error!", "No name provided!");
    }

    if (ui->manager_LineEdit->text() == "")
    {
        checker = false;
        QMessageBox::about(this,"Error!", "No manager provided!");
    }

    if (checker)
    {
        if (!Editing)

        {
            myQuery.prepare("SELECT * FROM add_branch(:_city, :_name, :_manager)");
            myQuery.bindValue(":_city", ui->city_LineEdit->text());
            myQuery.bindValue(":_name", ui->name_LineEdit->text());
            myQuery.bindValue(":_manager", ui->manager_LineEdit->text());
            checker = myQuery.exec();
            if (checker)
            {
                QMessageBox::about(this,"Welcome!", "New branch!");
                ui->city_LineEdit->setText("");
                ui->name_LineEdit->setText("");
                ui->manager_LineEdit->setText("");
            }
            if (!checker)
                QMessageBox::about(this,"Error!", "Something went wrong!");
        }
        else
        {
            myQuery.prepare("SELECT * FROM change_branch(:_oldname, :_newcity, :_newname, :_newmanager)");
            myQuery.bindValue(":_oldname", oldName);
            myQuery.bindValue(":_newcity", ui->city_LineEdit->text());
            myQuery.bindValue(":_newname", ui->name_LineEdit->text());
            myQuery.bindValue(":_newmanager", ui->manager_LineEdit->text());
            checker = myQuery.exec();
            if (checker)
            {
                trayIcon = new QSystemTrayIcon(this);
                trayIcon->setVisible(true);
                trayIcon->showMessage("We will miss them!", "You succesfully updated the branch info.");
            }
            if (!checker)
                QMessageBox::about(this,"Error!", "Something went wrong!");
        }

    }
}
