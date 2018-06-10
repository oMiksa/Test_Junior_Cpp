#ifndef PIRAMID_H
#define PIRAMID_H

#include <QMainWindow>
#include <QLabel>
#include <QImage>

namespace Ui {
class Piramid;
}

class Piramid : public QMainWindow
{
    Q_OBJECT

public:
    explicit Piramid(QWidget *parent = 0);

    void newLayer(QString path, int width, int height);

    ~Piramid();

    QImage *img;
private:
    Ui::Piramid *ui;
};

#endif // PIRAMID_H
