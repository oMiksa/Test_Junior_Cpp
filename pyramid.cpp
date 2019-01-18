#include "pyramid.h"
#include "ui_pyramid.h"
#include "new_coefficient.h"

double diagonal(const QImage *i)
{
    return qSqrt(qPow(i->height(), 2) + qPow(i->width(), 2));
}

bool diagonalMax(const QPair<QString, QImage*> &a, const QPair<QString, QImage*> &b)
{
    return (diagonal(a.second) < diagonal(b.second));
}

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

    cof = COF_PYRAMID;
    heigthPyramid = 1;
    img = new QVector<QPair<QString, QImage*>>;
    imgLbl = new QLabel(this);
    imgTemp = new QImage;

    for(int i(0); i < MAX_HEIGHT_PYRAMID + 1; i++) {
        ui->layerComboBox->addItem(QString::number(i));
    }
    indexlayer = ui->layerComboBox->currentIndex();

    startLayer(500,500);
}

Pyramid::Pyramid(QString path, QString coefficient, QWidget *parent) :
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

    cof = COF_PYRAMID;
    heigthPyramid = 1;
    img = new QVector<QPair<QString, QImage*>>;
    imgLbl = new QLabel(this);
    imgTemp = new QImage;

    for(int i(0); i < MAX_HEIGHT_PYRAMID + 1; i++) {
        ui->layerComboBox->addItem(QString::number(i));
    }
    indexlayer = ui->layerComboBox->currentIndex();

    setCofPyramid(coefficient.toDouble());

    newLayer(path);
}

void Pyramid::newLayer(QString path)
{
    QFileInfo fileName(path);
    QPair<QString, QImage*> p;
    p.first = fileName.fileName();
    p.second = new QImage(path);
    img->append(p);

    std::sort(img->begin(), img->end(), diagonalMax);

    indexPicture = newNameComboBox(fileName.fileName());

    block(true);

    creatPyramid();
}

void Pyramid::startLayer(int width, int height)
{
    pix = new QPixmap(width, height);
    pix->fill(Qt::white);
    imgLbl->setPixmap(*pix);
    ui->scrollArea->setWidget(imgLbl);

    //show size Pixmap
    ui->sizeLayerLabel->setText(QString::number(width) + "x" + QString::number(height));

    block(true);
}

void Pyramid::openImageLayer()
{
    QString paths = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files(*.png *.jpg)"));

    if(paths != "")
        newLayer(paths);
}

void Pyramid::layer()
{
    double coefficient = qPow(cof, indexlayer);
    *imgTemp = *img->at(indexPicture).second;
    *imgTemp = imgTemp->scaled(widthPicture / coefficient, heightPicture / coefficient, Qt::KeepAspectRatio)\
            .scaled(widthPicture, heightPicture, Qt::KeepAspectRatio);
    printLayer();
}

void Pyramid::printLayer()
{
    imgLbl->setPixmap(QPixmap::fromImage(*imgTemp));
    ui->scrollArea->setWidget(imgLbl);

    //show size Pixmap
    ui->sizeLayerLabel->setText(QString::number(widthPicture) + "x" + QString::number(heightPicture));
}

void Pyramid::creatPyramid()
{
    *imgTemp = *img->at(indexPicture).second;
    painter = new QPainter(imgTemp);

    tmr->start();
    printLayer();
}

void Pyramid::setCofPyramid(double c)
{
    if(c >= 1.0)
        cof = c;
}

Pyramid::~Pyramid()
{
    delete img;
    delete imgTemp;
    delete pix;
    delete painter;
    delete ui;
}

void Pyramid::block(bool status)
{
    ui->layerComboBox->setDisabled(status);
    ui->fileNameComboBox->setDisabled(status);
}

int Pyramid::newNameComboBox(QString name)
{
    ui->fileNameComboBox->clear();

    for(auto i = img->begin(); i != img->end(); i++)
        ui->fileNameComboBox->addItem(i->first);

    ui->fileNameComboBox->setCurrentText(name);
    return ui->fileNameComboBox->currentIndex();
}

void Pyramid::on_actionOpen_triggered()
{
    openImageLayer();
}

void Pyramid::compression()
{
    widthPicture = img->at(indexPicture).second->width();
    heightPicture = img->at(indexPicture).second->height();
    double coefficient = qPow(cof, heigthPyramid);

    painter->drawImage(widthPicture / 2 - widthPicture / (coefficient * 2), heightPicture / 2 - heightPicture / (coefficient * 2),\
                       img->at(indexPicture).second->scaled(widthPicture / coefficient, heightPicture / coefficient, Qt::KeepAspectRatio));
    printLayer();

    //pyramid is drawn, go to the first layer
    if(++heigthPyramid > MAX_HEIGHT_PYRAMID) {
        heigthPyramid = 1;
        tmr->stop();
        painter->end();
        block(false);
        layer();
    }
}

void Pyramid::on_fileNameComboBox_activated(int index)
{
    indexPicture = index;
    layer();
}

void Pyramid::on_layerComboBox_activated(int index)
{
    indexlayer = index;
    layer();
}

void Pyramid::on_actionNew_Coefficient_triggered()
{
    new_coefficient nc(&cof);
    nc.exec();
}
