#ifndef B_WORKER_H
#define B_WORKER_H

#include <QObject>
#include <QFile>
#include <QList>
#include <QTimer>


class BBworker : public QObject
{
	Q_OBJECT
public:
	explicit BBworker(QObject *parent = 0);

signals:
    void loadingFinished();

public slots:
    void startLoading();   

};




#endif // B_WORKER_H
