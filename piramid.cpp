#include "piramid.h"
#include "ui_piramid.h"

Piramid::Piramid(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Piramid)
{
    ui->setupUi(this);
}

Piramid::~Piramid()
{
    delete ui;
}
