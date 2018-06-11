#ifndef PIRAMID_H
#define PIRAMID_H

#include <QMainWindow>
#include <QLabel>
#include <QImage>
#include <QScrollArea>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>

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

    ~Piramid();

    QImage *img;
    QPixmap *pix;
private slots:
    void on_actionOpen_triggered();

private:
    Ui::Piramid *ui;
};

#endif // PIRAMID_H
