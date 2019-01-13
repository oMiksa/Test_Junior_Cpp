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
#include <QFileInfo>
#include <QTimer>
#include <QVector>
#include <QPair>
#include <QDebug>
#include <algorithm>

namespace Ui {
class Pyramid;
}

class Pyramid : public QMainWindow
{
    Q_OBJECT

public:
    explicit Pyramid(QWidget *parent = nullptr);
    explicit Pyramid(QString path, QString coefficient, QWidget *parent = nullptr);

    void openImageLayer();
    void layer();
    void setCofPyramid(double cof);
    ~Pyramid();

private slots:
    void compression();
    void on_actionOpen_triggered();
    void on_actionNew_Coefficient_triggered();
    void on_fileNameComboBox_activated();
    void on_layerComboBox_activated();


private:
    void block(bool status);
    void newNameComboBox(QString name);
    void newLayer(QString path);
    void startLayer(int width, int height);
    void printLayer();
    void creatPyramid();

    double cof;
    QVector<QPair<QString, QImage*>> *img;
    QImage *imgTemp;
    QTimer *tmr;
    QPixmap *pix;
    QLabel *imgLbl;
    QPainter *painter;

    Ui::Pyramid *ui;
};

#endif // PYRAMID_H
