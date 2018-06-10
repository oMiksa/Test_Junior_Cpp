#include "piramid.h"
#include "ui_piramid.h"

Piramid::Piramid(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Piramid)
{
    ui->setupUi(this);
    this->setFixedSize(550,600);

    newLayer(".//ImageClear.png",500,500);
}

void Piramid::newLayer(QString path, int width, int height)
{
    //ui->imageLabel->resize(width,height);
    img = new QImage(path);
    QImage qwe = img->scaled(width,height);
    ui->imageLabel->setPixmap(QPixmap::fromImage(qwe));
}

Piramid::~Piramid()
{
    delete ui;
}
