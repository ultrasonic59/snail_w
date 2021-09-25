#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include <QtPlugin>
#include <QTranslator>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
Q_IMPORT_PLUGIN(QICOPlugin)
Q_IMPORT_PLUGIN(DSServicePlugin)



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

/*	QTranslator qtPortTranslator;
	qtPortTranslator.load(":/q_win_weasel/main_ru.qm");
	a.installTranslator(&qtPortTranslator);
	QLocale::setDefault(QLocale(QLocale::Russian, QLocale::RussianFederation));*/

	MainWindow w;
	w.show();

	return a.exec();
}
