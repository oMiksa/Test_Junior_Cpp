#ifndef PYRAMID_H
#define PYRAMID_H

#define MAX_HEIGHT_PYRAMID 4
#define SPEED_PRINTING_PYRAMID 1500

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
    void Layer(int n);
    void printLayer();
    void printLayer(int n);
    void creatPyramid();

    ~Pyramid();

    QImage *img;// сделать мапу
    QImage *imgTemp;
    QTimer *tmr;
    QPixmap *pix;
    QLabel *imgLbl;
    QPainter *painter;

private slots:
    void on_actionOpen_triggered();
    void compression();

private:
    Ui::Pyramid *ui;
};

#endif // PYRAMID_H
