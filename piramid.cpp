#include "piramid.h"
#include "ui_piramid.h"

Piramid::Piramid(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Piramid)
{
    ui->setupUi(this);
    this->setFixedSize(550,600);
    //ui->imageLabel->setFixedSize(500,500);

    newLayer(250,250,".//ImageClear.png");
}

void Piramid::newLayer(int width, int height)
{
    pix = new QPixmap(width,height);
    pix->fill(Qt::white);
    ui->imageLabel->setPixmap(*pix);
    ui->sizeLayerLabel->setText(QString::number(width) + "x" + QString::number(height));
}

void Piramid::newLayer(int width, int height, QString path)
{
    img = new QImage(path);
    ui->imageLabel->setPixmap(QPixmap::fromImage(img->scaled(width,height)));
    ui->sizeLayerLabel->setText(QString::number(width) + "x" + QString::number(height));
}

Piramid::~Piramid()
{
    delete ui;
}
