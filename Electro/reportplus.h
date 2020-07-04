#ifndef REPORTPLUS_H
#define REPORTPLUS_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QStringListModel>
#include <QSqlQuery>


namespace Ui {
class reportPlus;
}

class reportPlus : public QDialog
{
    Q_OBJECT

public:
    explicit reportPlus(QWidget *parent = nullptr);
    ~reportPlus();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

private:
    Ui::reportPlus *ui;
    QSqlTableModel* variable;
    QStringList items;
    QSqlDatabase ElectroDB;
    int reportMode;
    QSqlQueryModel* myModel;
};

#endif // REPORTPLUS_H
