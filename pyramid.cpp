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
    img = new QVector<QPair<QString, QImage*>>;
    imgLbl = new QLabel(this);
    imgTemp = new QImage;

    for(int i(0); i < MAX_HEIGHT_PYRAMID + 1; i++) {
        ui->layerComboBox->addItem(QString::number(i));
    }

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
    img = new QVector<QPair<QString, QImage*>>;
    imgLbl = new QLabel(this);
    imgTemp = new QImage;

    for(int i(0); i < MAX_HEIGHT_PYRAMID + 1; i++) {
        ui->layerComboBox->addItem(QString::number(i));
    }

    setCofPyramid(coefficient.toDouble());
    qDebug() << path << coefficient.toDouble();
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

    newNameComboBox(fileName.fileName());

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
    *imgTemp = *img->at(ui->fileNameComboBox->currentIndex()).second;
    *imgTemp = imgTemp->scaled(img->at(ui->fileNameComboBox->currentIndex()).second->width() / (qPow(cof, ui->layerComboBox->currentIndex())),\
                               img->at(ui->fileNameComboBox->currentIndex()).second->height() / (qPow(cof, ui->layerComboBox->currentIndex())),\
                               Qt::KeepAspectRatio)\
            .scaled(img->at(ui->fileNameComboBox->currentIndex()).second->width(),\
                    img->at(ui->fileNameComboBox->currentIndex()).second->height(), Qt::KeepAspectRatio);
    printLayer();
}

void Pyramid::printLayer()
{
    imgLbl->setPixmap(QPixmap::fromImage(*imgTemp));
    ui->scrollArea->setWidget(imgLbl);

    //show size Pixmap
    ui->sizeLayerLabel->setText(QString::number(img->at(ui->fileNameComboBox->currentIndex()).second->width()) + "x" +\
                                QString::number(img->at(ui->fileNameComboBox->currentIndex()).second->height()));
}

void Pyramid::creatPyramid()
{
    *imgTemp = *img->at(ui->fileNameComboBox->currentIndex()).second;
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

void Pyramid::newNameComboBox(QString name)
{
    ui->fileNameComboBox->clear();

    for(auto i = img->begin(); i != img->end(); i++)
        ui->fileNameComboBox->addItem(i->first);

    ui->fileNameComboBox->setCurrentText(name);
}

void Pyramid::on_actionOpen_triggered()
{
    openImageLayer();
}

void Pyramid::compression()
{
    static int heigthPyramid = 1;
    painter->drawImage(img->at(ui->fileNameComboBox->currentIndex()).second->width() / 2 - \
                       img->at(ui->fileNameComboBox->currentIndex()).second->width() / (qPow(cof, heigthPyramid) * 2),\
                       img->at(ui->fileNameComboBox->currentIndex()).second->height() / 2 - \
                       img->at(ui->fileNameComboBox->currentIndex()).second->height() / (qPow(cof, heigthPyramid) * 2),\
                       img->at(ui->fileNameComboBox->currentIndex()).second->scaled(\
                           img->at(ui->fileNameComboBox->currentIndex()).second->width() / qPow(cof, heigthPyramid),\
                               img->at(ui->fileNameComboBox->currentIndex()).second->height() / qPow(cof, heigthPyramid),\
                                   Qt::KeepAspectRatio));
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

void Pyramid::on_fileNameComboBox_activated()
{
    layer();
}

void Pyramid::on_layerComboBox_activated()
{
    layer();
}

void Pyramid::on_actionNew_Coefficient_triggered()
{
    new_coefficient nc(&cof);
    nc.exec();
}
