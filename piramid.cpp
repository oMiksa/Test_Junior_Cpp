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
    img = new QImage(path);
    QLabel *imgLbl = new QLabel(this);
    imgLbl->setPixmap(QPixmap::fromImage(*img));
    ui->scrollArea->setWidget(imgLbl);

    //show size Pixmap
    ui->sizeLayerLabel->setText(QString::number(img->height()) + "x" + QString::number(img->width()));
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

Piramid::~Piramid()
{
    delete ui;
}

void Piramid::on_actionOpen_triggered()
{
    openImageLayer();
}
