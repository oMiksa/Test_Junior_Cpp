#include "pyramid.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    switch (argc) {
    case 1: {
        QApplication a(argc, argv);
        Pyramid w;
        w.show();
        return a.exec();
    }
    case 3: {
        QApplication a(argc, argv);
        Pyramid w(argv[1], argv[2]);
        w.show();
        return a.exec();
    }
    default:
        printf("### Information ###\n");
        printf("first parametor -> path to picture\n");
        printf("second parametor -> coefficient\n");
    }

}
