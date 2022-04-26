#include "snail.h"
#include <QtWidgets/QApplication>
#include <qlabel.h>
#include <QtPlugin>
//Q_IMPORT_PLUGIN (QWindowsIntegrationPlugin)
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Snail w;
	
 
	w.show();
	return a.exec();
}
