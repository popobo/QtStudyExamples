#include "QtMocPropertyExample.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtMocPropertyExample w;
    w.show();
    return a.exec();
}
