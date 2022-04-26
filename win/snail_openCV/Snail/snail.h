#ifndef SNAIL_H
#define SNAIL_H

#include <QtWidgets/QMainWindow>
#include <QGuiApplication>
#include <QFileDialog>
#include <QColorDialog>
#include <QColor>
#include <QStateMachine>
#include <QFinalState>
#include "ui_snail.h"
#include "gridscene.h"
#include "cursorposlabel.h"
#include "BoardPoinsModel.h"

class Snail : public QMainWindow
{
	Q_OBJECT

public:
	Snail(QWidget *parent = 0);
	~Snail();
public slots:
		void on_btnLoad_clicked();
		void on_btnAdjustImg_clicked();
		void on_btnAdjGrid_clicked();
		void on_btnUploadPoints_clicked();

		
		void slotSetInitialState();
		void update();
signals:
		void adjustImgFinished();
private:
	CursorPosLabel* cursorPosLabel;
	Ui::SnailClass ui;
	BoardPointsModel* boardPointsModel;
	QStateMachine machine;
	QFinalState *finalState;
    QState *initialState ;
	bool stateMachineFlag;

	void additionalSetupUI();
	void connectSignals(void);
	void settingStateMachine(Ui::SnailClass& my_ui);
	void setStateMachineInInitialState();
	void setUpdateBtnTimer();
};

#endif // SNAIL_H
