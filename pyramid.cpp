#include "pyramid.h"
#include "ui_pyramid.h"

Pyramid::Pyramid(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Pyramid)
{
    ui->setupUi(this);

    tmr = new QTimer(this);
    tmr->setInterval(SPEED_PRINTING_PYRAMID);
    connect(tmr, SIGNAL(timeout()), this, SLOT(compression()));

    this->setFixedSize(550,600);
    ui->fileNameComboBox->setFixedSize(120,20);
    ui->scrollArea->setFixedSize(502,504);
    ui->scrollArea->setBackgroundRole(QPalette::Dark);

    initLayer(500,500);
}

void Pyramid::newLayer(QString path)
{
    img = new QImage(path);
    imgTemp = new QImage(path);

    creatPyramid();
}

void Pyramid::initLayer(int width, int height)
{
    pix = new QPixmap(width, height);
    pix->fill(Qt::white);
    imgLbl = new QLabel(this);
    imgLbl->setPixmap(*pix);
    ui->scrollArea->setWidget(imgLbl);

    //show size Pixmap
    ui->sizeLayerLabel->setText(QString::number(width) + "x" + QString::number(height));
}

void Pyramid::openImageLayer()
{
    QString paths = QFileDialog::getOpenFileName(this,tr("Open Image"),"",tr("Image Files(*.png *.jpg)"));
    QFileInfo fileName(paths);
    ui->fileNameComboBox->addItem(fileName.fileName());
    newLayer(paths);
}

void Pyramid::Layer(int n)
{
    *imgTemp = *img;
    *imgTemp = imgTemp->scaled(img->width() / qFloor(qPow(2, n)), img->height() / qFloor(qPow(2, n)), Qt::KeepAspectRatio)\
            .scaled(img->width(), img->height(), Qt::KeepAspectRatio);
    printLayer(n);
}

void Pyramid::printLayer()
{
    imgLbl->setPixmap(QPixmap::fromImage(*imgTemp));
    ui->scrollArea->setWidget(imgLbl);

    //show size Pixmap
    ui->sizeLayerLabel->setText(QString::number(imgTemp->width()) + "x" + QString::number(imgTemp->height()));
}

void Pyramid::printLayer(int n)
{
    imgLbl->setPixmap(QPixmap::fromImage(*imgTemp));
    ui->scrollArea->setWidget(imgLbl);

    //show size Pixmap
    ui->sizeLayerLabel->setText(QString::number(imgTemp->width() / qFloor(qPow(2, n))) + "x"\
                                + QString::number(imgTemp->height() / qFloor(qPow(2, n))));
}

void Pyramid::creatPyramid()
{
    painter = new QPainter(imgTemp);
    tmr->start();
    printLayer();

}

Pyramid::~Pyramid()
{
    delete ui;
}

void Pyramid::on_actionOpen_triggered()
{
    openImageLayer();
}

void Pyramid::compression()
{
    static int heigthPyramid = 1;
    painter->drawImage(img->width() / 2 - img->width() / qFloor(qPow(2, heigthPyramid) * 2),\
                       img->height() / 2 - img->height() / qFloor(qPow(2, heigthPyramid) * 2),\
                       img->scaled(img->width() / qFloor(qPow(2, heigthPyramid)),\
                                   img->height() / qFloor(qPow(2, heigthPyramid)),\
                                   Qt::KeepAspectRatio));
    printLayer();

    //pyramid is drawn, go to the first layer
    if(++heigthPyramid > MAX_HEIGHT_PYRAMID) {
        heigthPyramid = 1;
        tmr->stop();
        painter->end();
        Layer(4);
    }
}
