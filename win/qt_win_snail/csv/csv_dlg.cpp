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
void csv_dlg::set_dat_col(int num_row, int num_col, QString irec) {
    QString trec=irec.mid(1);
    trec.chop(1);
    char *char_str;
    std::string str = trec.toStdString();
    const char* tstr = str.c_str();
    switch (num_col) {
    case 0:
        strcpy(t_element_data.RefDes, tstr);
        break;
    case 1:
        ///      p_sn_data->
        ///       qDebug() << "rec= " << tstr;
        strcpy(t_element_data.PatternName, tstr);
        break;
    case 2:
        ///qDebug() << "rec= " << tstr;
        break;
    case 3:
        t_element_data.Layer = (trec == "Top") ? false : true;
        break;
    case 4:
    {
        float ftmp;
        ftmp = trec.toFloat();
        t_element_data.cvs_pos.LocationX = ftmp;

 ///       qDebug() << "trec= " << trec << ftmp << t_element_data.cvs_pos.LocationX;
    }
        break;
    case 5:
        t_element_data.cvs_pos.LocationY = trec.toFloat();
        break;
    case 6:
        t_element_data.cvs_pos.Rotation = trec.toFloat();
        break;
    case 7:
        t_element_data.check = (trec == "") ? false : true;
        break;
    }
}

bool csv_dlg::conv_data()
{
    if (p_sn_data == nullptr)
        return false;
    QString tstr= QString();
    QStandardItem* item;

    QList<QStandardItem*> itemList;
    QModelIndex index = csvModel->index(0,0);
    for (int ii = 1; ii < csvModel->rowCount(); ii++) {
        for (int jj = 0; jj < csvModel->columnCount(); jj++) {
            index = csvModel->index(ii,jj);
                tstr = index.data().toString();
             ///   qDebug() << "tstr= " << tstr;
           set_dat_col(ii, jj, tstr);
        }
    p_sn_data->elements << t_element_data;
}
    return true;
}
void csv_dlg::SlotSaveFile()
{
  if (!conv_data())
      return;
  element_data_t t_elem_data;
  float min_x = 0;
  float min_y = 0;
  float max_x = 0;
  float max_y = 0;
  ///int num_el = 0;

  QString fileName_tbl = fileName_csv;
  fileName_tbl.chop(3);
  fileName_tbl += "tbl";
  qDebug() << "fileName_tbl= " << fileName_tbl;
  QFile file(fileName_tbl);
 
  if (!file.open(QIODevice::WriteOnly)) {
      QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
      return;
  }
 
  int cnt_el=p_sn_data->elements.count();
  qDebug() << "cnt_el= " << cnt_el;
  for (int ii = 0; ii < cnt_el; ii++) {
  ///    t_elem_data << p_sn_data->elements;
      t_elem_data = p_sn_data->elements.takeFirst();
    /// qDebug() << "el= " << t_elem_data.cvs_pos.LocationX;/// check;/// .Layer;

      file.write( (const char*) &t_elem_data,sizeof(element_data_t));
      if (min_x > t_elem_data.cvs_pos.LocationX)
          min_x = t_elem_data.cvs_pos.LocationX;
      if (min_y > t_elem_data.cvs_pos.LocationY)
          min_y = t_elem_data.cvs_pos.LocationY;
      if (max_x < t_elem_data.cvs_pos.LocationX)
          max_x = t_elem_data.cvs_pos.LocationX;
      if (max_y < t_elem_data.cvs_pos.LocationY)
          max_y = t_elem_data.cvs_pos.LocationY;
  }
file.close();
p_sn_data->max_x = max_x;
p_sn_data->max_y = max_y;
p_sn_data->min_x = min_x;
p_sn_data->min_y = min_y;
p_sn_data->num_elem = cnt_el;

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
        qDebug() << "num_comp= "<< num_comp;

        file.close();
    }
}