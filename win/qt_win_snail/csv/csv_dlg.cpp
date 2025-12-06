#include "csv_dlg.h"

csv_dlg::csv_dlg(QWidget* parent, c_snail_data* sn_data) :
    QDialog(parent, Qt::Window), pParent(parent), p_sn_data(sn_data)
    , ui()
{
    ui.setupUi(this);

connect(ui.pushButtonOpen, SIGNAL(clicked()), this, SLOT(SlotOpenFile()));
connect(ui.pushButtonSave, SIGNAL(clicked()), this, SLOT(SlotSaveFile()));

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
void csv_dlg::set_dat_col(int num_row, int num_col, QString rec) {
    QString trec=rec;
    char *tstr = trec.toStdString().c_str();
  ///  trec.chop(3);
  ///  tstr = trec.toStdString().c_str();
    switch (num_col) {
    case 1:
         qDebug() << "rec= " << trec;

        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;

    }

}

void csv_dlg::conv_data()
{
    QString tstr= QString();
    QStandardItem* item;
    QList<QStandardItem*> itemList;
    QModelIndex index = csvModel->index(0,0);
    for (int ii = 1; ii < csvModel->rowCount(); ii++) {
        for (int jj = 0; jj < csvModel->columnCount(); jj++) {
            index = csvModel->index(ii,jj);
                tstr = index.data().toString();
             ///   qDebug() << "tstr= " << tstr;
//            }
           set_dat_col(ii, jj, tstr);
        }
}

}
void csv_dlg::SlotSaveFile()
{
    conv_data();
}
void csv_dlg::SlotOpenFile()
{
    quint32 num_comp = 0;
    csvModel = new QStandardItemModel(this);
    csvModel->setColumnCount(CSV_NUM_COL+1);   /// +1 for check
     ui.tableView->setModel(csvModel); // Устанавливаем модель в таблицу
  ////  csvModel->setHorizontalHeaderLabels(QStringList() << "Марка" << "Модель" << "Цена");

     fileName_csv = QFileDialog::getOpenFileName(this, tr("Open File"), "",
        tr("Csv Files (*.csv *.pnp )"));
      if (fileName_csv != "") {
        QFile file(fileName_csv);
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
     head_list << "Check";

     csvModel->setHorizontalHeaderLabels(head_list);

     while (!in.atEnd())
        {
            // ... построчно
            QString line = in.readLine();
            // Добавляем в модель по строке с элементами
            QList<QStandardItem*> standardItemsList;
           
            for (QString item : line.split(",")) {
       ///         qDebug() << "item= " << item;

                standardItemsList.append(new QStandardItem(item));
            }
            csvModel->insertRow(csvModel->rowCount(), standardItemsList);
            num_comp++;
        }
        ////qDebug() << "num_comp= "<< num_comp;

        file.close();
    }
}