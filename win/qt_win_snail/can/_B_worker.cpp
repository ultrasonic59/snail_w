#include <QThread>
#include <QDebug>
#include "B_worker.h"


BBworker::BBworker(QObject *parent) : 
			QObject(parent)
{

}

void BBworker::startLoading() {
// Your file loading logic goes here
// Emit the loadingFinished signal when loading is complete
	emit loadingFinished();
}