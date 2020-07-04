#ifndef PAYMENT_H
#define PAYMENT_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class payment;
}

class payment : public QDialog
{
    Q_OBJECT

public:
    explicit payment(QString name, bool isEditing);
    ~payment();

private slots:
    void on_saveButton_clicked();

private:
    Ui::payment *ui;
    QString oldName;
    bool Editing;
    QSqlDatabase ElectroDB;

};

#endif // PAYMENT_H
