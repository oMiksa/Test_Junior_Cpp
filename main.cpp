#include "piramid.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Piramid w;
    w.show();

    return a.exec();
}
