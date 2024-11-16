#ifndef SCRIPTWINDOW_H
#define SCRIPTWINDOW_H

#include <QtGui>
#include <QtScript>

class SDialog : public QDialog
{
	Q_OBJECT

public:
	SDialog(QWidget *parent) : QDialog(parent) {};
	
public slots:
	void setPosition(int x, int y, int w, int h ){
		setGeometry ( x, y, w, h );
	};

};

class SPushButton : public QPushButton
{
	Q_OBJECT

public:
	SPushButton(QWidget *parent) : QPushButton(parent) {};
	
public slots:
	void setPosition(int x, int y, int w, int h ){
		setGeometry ( x, y, w, h );
	};

};

class STextEdit : public QTextEdit
{
	Q_OBJECT

public:
	STextEdit(QWidget *parent) : QTextEdit(parent) {};
	
public slots:
	void setPosition(int x, int y, int w, int h ){
		setGeometry ( x, y, w, h );
	};

};

class SLabel : public QLabel
{
	Q_OBJECT

public:
	SLabel(QWidget *parent) : QLabel(parent) {};
	
public slots:
	void setPosition(int x, int y, int w, int h ){
		setGeometry ( x, y, w, h );
	};

};

#endif
