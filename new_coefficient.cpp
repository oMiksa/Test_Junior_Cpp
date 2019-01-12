#include "new_coefficient.h"
#include "ui_new_coefficient.h"

new_coefficient::new_coefficient(double *coefficient, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_coefficient)
{
    cof = coefficient;
    ui->setupUi(this);
}

new_coefficient::~new_coefficient()
{
    delete ui;
}

void new_coefficient::on_pushButtonOk_clicked()
{
    *cof = ui->lineEdit->text().toDouble();
    close();
}

void new_coefficient::on_pushButtonClose_clicked()
{
    close();
}
