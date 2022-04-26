#include "snail.h"
#include <QDesktopWidget>
#include "boardsizedlg.h"
Snail::Snail(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
	additionalSetupUI();

	boardPointsModel=new BoardPointsModel();
	ui.listView->setModel(boardPointsModel);

	connectSignals();

	initialState = new QState();
	finalState = new QFinalState();
	settingStateMachine(ui);
	setStateMachineInInitialState();



}

Snail::~Snail()
{

}
void Snail::on_btnLoad_clicked()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	QString fileName = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.jpg *.png");
	if(fileName.isEmpty())
	{
		QApplication::restoreOverrideCursor();	
		return;
	}
	GridScene* gridScene=reinterpret_cast<GridScene*>(ui.graphicsView->scene());
	gridScene->loadOpenCVImg(fileName);
	ui.graphicsView->fitInView(gridScene->pixmapItem(),Qt::KeepAspectRatio);
	QApplication::restoreOverrideCursor();

	if(!stateMachineFlag)
	{
		initialState->addTransition(ui.btnLoad, SIGNAL(clicked()), finalState);
		stateMachineFlag=true;
	}

}
void Snail::on_btnAdjustImg_clicked()
{	


	BoardSizeDlg* dlg=new BoardSizeDlg(this);
	if(dlg->exec()==QDialog::Accepted){
		QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
		GridScene* gridScene=reinterpret_cast<GridScene*>(ui.graphicsView->scene());
		gridScene->adjustBoardImg(dlg->boardSize());
		QApplication::restoreOverrideCursor();	
		emit adjustImgFinished();
	}
	delete dlg;

	//ui.graphicsView->fitInView(gridScene->pixmapItem());

}


void Snail::on_btnAdjGrid_clicked()
{
	GridScene* gridScene=reinterpret_cast<GridScene*>(ui.graphicsView->scene());

	gridScene->adjustGrid();
	ui.graphicsView->setMouseTracking(true);
	gridScene->setModel(boardPointsModel);
	setUpdateBtnTimer();

}

void Snail::on_btnUploadPoints_clicked()
{
	//TODO model must clear from elrments;scene must redraw (модель должна очищаться от элементов ;сцена перерисовываться)
	//boardPointsModel->clear();
		GridScene* gridScene=reinterpret_cast<GridScene*>(ui.graphicsView->scene());
		gridScene->clearScene();
}

void Snail::additionalSetupUI()
{
	cursorPosLabel=new CursorPosLabel(this);
	statusBar()->addPermanentWidget(cursorPosLabel);
	QLabel* statusRight = new QLabel("Right", this);
	statusRight->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	statusBar()->addPermanentWidget(statusRight,1);


}


void Snail::connectSignals()
{
	connect(ui.graphicsView->scene(),SIGNAL(changeCursorPosition(const QString&)),cursorPosLabel,SLOT(ChangeLabelText(const QString&)));

}



void Snail::settingStateMachine(Ui::SnailClass& my_ui)
{
	machine.addState(initialState);
	machine.addState(finalState);

	QState *s11 = new QState(initialState);
	QState *s21 = new QState(initialState);
	QState *s31 = new QState(initialState);
	QState *s41 = new QState(initialState);
	

	s11->assignProperty(my_ui.btnLoad,"enabled",true);
	s11->assignProperty(my_ui.btnAdjustImg,"enabled",false);
	s11->assignProperty(my_ui.btnAdjGrid,"enabled",false);
	s11->assignProperty(my_ui.btnUploadPoints,"enabled",false);


	s21->assignProperty(my_ui.btnLoad,"enabled",true);
	s21->assignProperty(my_ui.btnAdjustImg,"enabled",true);
	s21->assignProperty(my_ui.btnAdjGrid,"enabled",false);
	s21->assignProperty(my_ui.btnUploadPoints,"enabled",false);

	s31->assignProperty(my_ui.btnLoad,"enabled",true);
	s31->assignProperty(my_ui.btnAdjustImg,"enabled",false);
	s31->assignProperty(my_ui.btnAdjGrid,"enabled",true);
	s31->assignProperty(my_ui.btnUploadPoints,"enabled",false);


	s41->assignProperty(my_ui.btnLoad,"enabled",true);
	s41->assignProperty(my_ui.btnAdjustImg,"enabled",false);
	s41->assignProperty(my_ui.btnAdjGrid,"enabled",false);
	s41->assignProperty(my_ui.btnUploadPoints,"enabled",true);

	initialState->setInitialState(s11);

	s11->addTransition(my_ui.btnLoad, SIGNAL(clicked()), s21);
	s21->addTransition(this, SIGNAL(adjustImgFinished()), s31);
	s31->addTransition(my_ui.btnAdjGrid, SIGNAL(clicked()), s41);

	initialState->addTransition(my_ui.btnUploadPoints, SIGNAL(clicked()), finalState);

	connect(&machine, SIGNAL(finished()),this, SLOT(slotSetInitialState()));



}
void Snail::setStateMachineInInitialState()
{
	stateMachineFlag=false;
	machine.setInitialState(initialState);
	machine.start();
}
void Snail::slotSetInitialState()
{
	boardPointsModel->clear();

	setStateMachineInInitialState();
}
void Snail::setUpdateBtnTimer()
{
	QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);
}

void Snail::update()
{

	if(boardPointsModel->rowCount(QModelIndex())==0)
	{
		ui.btnUploadPoints->setEnabled(false);
		return;
	}
	else 
		ui.btnUploadPoints->setEnabled(true);
}