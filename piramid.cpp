#include "piramid.h"
#include "ui_piramid.h"

Piramid::Piramid(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Piramid)
{
    ui->setupUi(this);

    this->setFixedSize(550,600);
    ui->fileNameComboBox->setFixedSize(120,20);
    ui->scrollArea->setFixedSize(502,504);
    ui->scrollArea->setBackgroundRole(QPalette::Dark);

    newLayer(500,500);
}

void Piramid::newLayer(QString path)
{
    imgLbl = new QLabel(this);
    img = new QImage(path);
    imgTemp = new QImage(path);

    nextLayer(ANOUNT);

    creatPyramid(4);

    nextLayer(3);



}

void Piramid::newLayer(int width, int height)
{
    pix = new QPixmap(width, height);
    pix->fill(Qt::white);
    QLabel *imgLbl = new QLabel(this);
    imgLbl->setPixmap(*pix);
    ui->scrollArea->setWidget(imgLbl);

    //show size Pixmap
    ui->sizeLayerLabel->setText(QString::number(width) + "x" + QString::number(height));
}

void Piramid::openImageLayer()
{
    QString paths = QFileDialog::getOpenFileName(this,tr("Open Image"),"",tr("Image Files(*.png *.jpg)"));
    QFileInfo fileName(paths);
    ui->fileNameComboBox->addItem(fileName.fileName());
    newLayer(paths);
}

void Piramid::nextLayer(int n)
{
    imgTemp->scaled(imgTemp->width() / qPow(2, n), imgTemp->height() / qPow(2, n), Qt::KeepAspectRatio)\
            .scaled(img->width(), img->height(), Qt::KeepAspectRatio);
    printLayer();
}

void Piramid::printLayer()
{
    imgLbl->setPixmap(QPixmap::fromImage(*imgTemp));
    ui->scrollArea->setWidget(imgLbl);

    //show size Pixmap
    ui->sizeLayerLabel->setText(QString::number(imgTemp->width()) + "x" + QString::number(imgTemp->height()));
}

void Piramid::creatPyramid(int n)
{
    QPainter painter(imgTemp);
    for(int i(1); i <= n; i++) {
        painter.drawImage(img->width() / 2 - img->width() / (qPow(2, i) * 2), img->height() / 2 - img->height() / (qPow(2, i) * 2),\
                          img->scaled(img->width() / qPow(2, i),img->height() / qPow(2, i),  Qt::KeepAspectRatio));
        printLayer();
    }
    painter.end();
}

Piramid::~Piramid()
{
    delete ui;
}

void Piramid::on_actionOpen_triggered()
{
    openImageLayer();
}
