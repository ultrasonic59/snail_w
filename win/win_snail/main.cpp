#include "win_snail.h"
#include <QtWidgets/QApplication>

#pragma comment(lib, "comctl32.lib")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    win_snail w;
    w.show();
    return a.exec();
}
