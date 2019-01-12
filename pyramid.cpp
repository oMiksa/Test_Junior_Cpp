#include "pyramid.h"
#include "ui_pyramid.h"
#include "new_coefficient.h"

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
    imgTemp = new QImage(path);
    imgs->append(*imgTemp);
    // !!имена сортировать по разрешению


    ui->layerComboBox->setDisabled(true);
    ui->fileNameComboBox->setDisabled(true);

    creatPyramid();
}

void Pyramid::initLayer(int width, int height)
{
    cof = COF_PYRAMID;
    imgs = new QVector<QImage>;
    pix = new QPixmap(width, height);
    pix->fill(Qt::white);
    imgLbl = new QLabel(this);
    imgLbl->setPixmap(*pix);
    ui->scrollArea->setWidget(imgLbl);

    ui->layerComboBox->setDisabled(true);
    ui->fileNameComboBox->setDisabled(true);

    for(int i(0); i < MAX_HEIGHT_PYRAMID + 1; i++) {
        ui->layerComboBox->addItem(QString::number(i));
    }

    //show size Pixmap
    ui->sizeLayerLabel->setText(QString::number(width) + "x" + QString::number(height));
}

void Pyramid::openImageLayer()
{
    // !!обработка при не выбраном файле
    QString paths = QFileDialog::getOpenFileName(this,tr("Open Image"),"",tr("Image Files(*.png *.jpg)"));
    QFileInfo fileName(paths);
    ui->fileNameComboBox->addItem(fileName.fileName());
    ui->fileNameComboBox->setCurrentText(fileName.fileName());
    newLayer(paths);
}

void Pyramid::Layer()
{
    *imgTemp = imgs->at(ui->fileNameComboBox->currentIndex());
    *imgTemp = imgTemp->scaled(imgs->at(ui->fileNameComboBox->currentIndex()).width() / (qPow(cof, ui->layerComboBox->currentIndex())),\
                               imgs->at(ui->fileNameComboBox->currentIndex()).height() / (qPow(cof, ui->layerComboBox->currentIndex())),\
                               Qt::KeepAspectRatio)\
            .scaled(imgs->at(ui->fileNameComboBox->currentIndex()).width(),\
                    imgs->at(ui->fileNameComboBox->currentIndex()).height(), Qt::KeepAspectRatio);
    printLayer();
}

void Pyramid::printLayer()
{
    imgLbl->setPixmap(QPixmap::fromImage(*imgTemp));
    ui->scrollArea->setWidget(imgLbl);

    //show size Pixmap
    ui->sizeLayerLabel->setText(QString::number(imgs->at(ui->fileNameComboBox->currentIndex()).width()) + "x" +\
                                QString::number(imgs->at(ui->fileNameComboBox->currentIndex()).height()));
}

void Pyramid::creatPyramid()
{
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
    delete imgs;
    delete imgTemp;
    delete pix;
    delete painter;
    delete ui;
}

void Pyramid::on_actionOpen_triggered()
{
    openImageLayer();
}

void Pyramid::compression()
{
    static int heigthPyramid = 1;
    painter->drawImage(imgs->at(ui->fileNameComboBox->currentIndex()).width() / 2 - \
                       imgs->at(ui->fileNameComboBox->currentIndex()).width() / (qPow(cof, heigthPyramid) * 2),\
                       imgs->at(ui->fileNameComboBox->currentIndex()).height() / 2 - \
                       imgs->at(ui->fileNameComboBox->currentIndex()).height() / (qPow(cof, heigthPyramid) * 2),\
                       imgs->at(ui->fileNameComboBox->currentIndex())\
                       .scaled(imgs->at(ui->fileNameComboBox->currentIndex()).width() / qPow(cof, heigthPyramid),\
                               imgs->at(ui->fileNameComboBox->currentIndex()).height() / qPow(cof, heigthPyramid),\
                                   Qt::KeepAspectRatio));
    printLayer();

    //pyramid is drawn, go to the first layer
    if(++heigthPyramid > MAX_HEIGHT_PYRAMID) {
        heigthPyramid = 1;
        tmr->stop();
        painter->end();
        ui->fileNameComboBox->setDisabled(false);
        ui->layerComboBox->setDisabled(false);
        Layer();
    }
}

void Pyramid::on_fileNameComboBox_activated(const QString &arg1)
{
    Layer();
}

void Pyramid::on_layerComboBox_activated(const QString &arg1)
{
    Layer();
}

void Pyramid::on_actionNew_Coefficient_triggered()
{
    new_coefficient nc(&cof);
    nc.exec();
}
