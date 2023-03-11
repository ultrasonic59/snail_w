#ifndef DIALOG_WRITE_FILE_H
#define DIALOG_WRITE_FILE_H

#include <QDialog>
#include "ui_dialog_write_file.h"

class Dialog_write_file : public QDialog
{
Q_OBJECT

protected:
	Ui::Dialog_write_file ui;

public:
	Dialog_write_file(QWidget *parent, const QString &file_path, const QString &write_dir);
	~Dialog_write_file();

	void GetFilePathAndWrDir(QString *file_path, QString *write_dir);


public slots:
	void on_file_path();

};

#endif // DIALOG_WRITE_FILE_H
