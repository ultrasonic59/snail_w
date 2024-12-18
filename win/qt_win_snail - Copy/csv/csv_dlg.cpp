﻿#include "csv_dlg.h"

csv_dlg::csv_dlg(QWidget* parent) :
    QDialog(parent, Qt::Window), pParent(parent)
    , ui()
{
    ui.setupUi(this);

connect(ui.pushButtonFile, SIGNAL(clicked()), this, SLOT(SlotOpenFile()));

}

csv_dlg::~csv_dlg()
{
    /*
    disconnect(this, SIGNAL(req_rd_dbg(int, dbg_dat_req_t*)), pParent, SLOT(slot_rd_dbg(int, dbg_dat_req_t*)));
    disconnect(this, SIGNAL(req_wr_dbg(int, dbg_dat_req_t*)), pParent, SLOT(slot_wr_dbg(int, dbg_dat_req_t*)));
    disconnect(this, SIGNAL(req_send_can_dbg(can_message_t*)), pParent, SLOT(slot_send_can_dbg(can_message_t*)));
    disconnect(ui.pushButton_send_can, SIGNAL(clicked()), this, SLOT(slot_send_can_msg()));
*/
}
#if 0
newAct = new QAction(QIcon(":/images/new.png"), tr("&Новый"), this);
//Параметры конструктора QAction: иконка из ресурсов, текст меню, родитель
newAct->setShortcuts(QKeySequence::New);
//В классе QKeySequence уже определены стандартные комбинации клавиш
newAct->setStatusTip(tr("Создать новый файл"));
//Подсказка для строки состояния;
//tr() - макрос, который может пригодиться
//при автоматической локализации приложения
connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));
//Назначили слот для обработки выбора пункта меню
#endif


void csv_dlg::SlotOpenFile()
{
    // Создаём модель данных для отображения таблицы из CSV файла
    csvModel = new QStandardItemModel(this);
    csvModel->setColumnCount(CSV_NUM_COL);
 ///   csvModel->setHorizontalHeaderLabels(QStringList() << "Марка" << "Модель" << "Цена");
    ui.tableView->setModel(csvModel); // Устанавливаем модель в таблицу
  ////  csvModel->setHorizontalHeaderLabels(QStringList() << "Марка" << "Модель" << "Цена");


QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
        tr("Csv Files (*.csv *.pnp)"));
  ////      tr("Csv Files (*.csv);;C++ Files (*.cpp *.h)"));
    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
     QTextStream in(&file);
     QStringList head_list;
     QString head_line = in.readLine();
     for (QString h_item : head_line.split(",")) {
         head_list<< h_item;
     }
     csvModel->setHorizontalHeaderLabels(head_list);

     while (!in.atEnd())
        {
            // ... построчно
            QString line = in.readLine();
            // Добавляем в модель по строке с элементами
            QList<QStandardItem*> standardItemsList;
            for (QString item : line.split(",")) {
                standardItemsList.append(new QStandardItem(item));
            }
            csvModel->insertRow(csvModel->rowCount(), standardItemsList);
        }
        file.close();
    }
}