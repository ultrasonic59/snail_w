#include "win_snail.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    win_snail w;
    w.show();
    return a.exec();
}
