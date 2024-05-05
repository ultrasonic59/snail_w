#pragma once
#include <QWidget>

class plotterwidget : public QWidget
{
public:
	plotterwidget(QWidget *parent=0);
///	plotterwidget(QWidget* parent = 0, Qt::WindowFlags f = 0);
	~plotterwidget(void);
   QImage image;

public slots:
	void _setImage(QImage);

protected:
    void paintEvent(QPaintEvent *);
	void resizeEvent(QResizeEvent *event);
};

