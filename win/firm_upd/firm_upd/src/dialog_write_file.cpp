#include "dialog_write_file.h"
#include "QFileDialogCust.h"

Dialog_write_file::Dialog_write_file(QWidget *parent, const QString &file_path, const QString &write_dir)
	: QDialog(parent, Qt::Window),
	ui()
{
	ui.setupUi(this);

	ui.lineEdit_file_path->setText(file_path);
	ui.lineEdit_dir->setText(write_dir);

}

Dialog_write_file::~Dialog_write_file()
{

}

void Dialog_write_file::GetFilePathAndWrDir(QString *file_path, QString *write_dir)
{
	*file_path = ui.lineEdit_file_path->text();
	*write_dir = ui.lineEdit_dir->text();
}


void Dialog_write_file::on_file_path()
{
	QFileDialogCust dial_file_sel(this);

	dial_file_sel.setFileMode(QFileDialog::ExistingFile);


	QDir old_dir(ui.lineEdit_file_path->text().section('/',0, -2));
	if(old_dir.exists())
		dial_file_sel.setDirectory(old_dir.path());
	else
		dial_file_sel.setDirectory(QCoreApplication::applicationDirPath());


	dial_file_sel.setOption(QFileDialog::DontUseNativeDialog, true);
	dial_file_sel.setNameFilter("*.*");

	dial_file_sel.setWindowTitle(tr("\320\227\320\260\320\277\320\270\321\201\321\213\320\262\320\260\320\265\320\274\321\213\320\271 \321\204\320\260\320\271\320\273"));


	dial_file_sel.show();
	if(dial_file_sel.exec())
	{
		QStringList temp = dial_file_sel.selectedFiles();
		ui.lineEdit_file_path->setText(temp[0]);
	}
}
