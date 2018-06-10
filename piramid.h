#ifndef PIRAMID_H
#define PIRAMID_H

#include <QMainWindow>

namespace Ui {
class Piramid;
}

class Piramid : public QMainWindow
{
    Q_OBJECT

public:
    explicit Piramid(QWidget *parent = 0);
    ~Piramid();

private:
    Ui::Piramid *ui;
};

#endif // PIRAMID_H
