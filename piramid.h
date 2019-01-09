#ifndef PIRAMID_H
#define PIRAMID_H

#define ANOUNT 7

#include <QMainWindow>
#include <QLabel>
#include <QImage>
#include <QList>
#include <QtMath>
#include <QPainter>
#include <QScrollArea>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QTimer>

namespace Ui {
class Piramid;
}

class Piramid : public QMainWindow
{
    Q_OBJECT

public:
    explicit Piramid(QWidget *parent = 0);

    void newLayer(QString path);
    void newLayer(int width, int height);
    void openImageLayer();
    void nextLayer(int n);
    void printLayer();
    void creatPyramid(int n);

    ~Piramid();

    QImage *img;
    QImage *imgTemp;
    QPixmap *pix;
    QLabel *imgLbl;

private slots:
    void on_actionOpen_triggered();

private:
    Ui::Piramid *ui;
};

#endif // PIRAMID_H
