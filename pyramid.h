#ifndef PYRAMID_H
#define PYRAMID_H

#define MAX_HEIGHT_PYRAMID 4
#define SPEED_PRINTING_PYRAMID 1500
#define COF_PYRAMID 2

#include <QMainWindow>
#include <QLabel>
#include <QImage>
#include <QtMath>
#include <QPainter>
#include <QScrollArea>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QTimer>
#include <QVector>
#include <QDebug>

namespace Ui {
class Pyramid;
}

class Pyramid : public QMainWindow
{
    Q_OBJECT

public:
    explicit Pyramid(QWidget *parent = 0);

    void newLayer(QString path);
    void initLayer(int width, int height);
    void openImageLayer();
    void Layer();
    void printLayer();
    void creatPyramid();
    void setCofPyramid(double cof);

    ~Pyramid();

    double cof;
    QVector<QImage> *imgs;
    QImage *imgTemp;
    QTimer *tmr;
    QPixmap *pix;
    QLabel *imgLbl;
    QPainter *painter;

private slots:
    void compression();
    void on_actionOpen_triggered();
    void on_actionNew_Coefficient_triggered();
    void on_fileNameComboBox_activated(const QString &arg1);
    void on_layerComboBox_activated(const QString &arg1);


private:
    Ui::Pyramid *ui;
};

#endif // PYRAMID_H
