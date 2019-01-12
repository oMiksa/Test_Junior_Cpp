#include "pyramid.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // !! запуск из командной строки
    QApplication a(argc, argv);
    Pyramid w;
    w.show();
    return a.exec();
}
