#ifndef BRANCH_H
#define BRANCH_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QString>
#include <QSystemTrayIcon>

namespace Ui {
class branch;
}

class branch : public QDialog
{
    Q_OBJECT

public:
    explicit branch(QString name, bool isEditing);
    ~branch();

private slots:
    void on_saveButton_clicked();

private:
    Ui::branch *ui;
    QSqlDatabase ElectroDB;
    bool Editing;
    QString oldCity;
    QString oldName;
    QSystemTrayIcon* trayIcon;

};

#endif // BRANCH_H
