#include "tbl_dlg.h"

tbl_dlg::tbl_dlg(QWidget* parent, c_snail_data* sn_data) :
    QDialog(parent, Qt::Window), pParent(parent), p_sn_data(sn_data)
    , ui()
{
    ui.setupUi(this);
 ///   void clicked(const QModelIndex & index);
 ///   void doubleClicked(const QModelIndex & index);

  ///  cellDoubleClicked
 //   tableWidget = ui.tableView;
///connect(ui.pushButtonOpen, SIGNAL(clicked()), this, SLOT(SlotOpenFile()));
 ///   connect(tableWidget, &QTableWidget::cellClicked, this, &tbl_dlg::onCellClicked);
  //  connect(ui.tableView, SIGNAL(cellClicked(int,int)), this, SLOT(onCellClicked(int,int)));
  //  connect(ui.tableView, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(onCellClicked(int, int)));
    connect(ui.tableView, SIGNAL(doubleClicked(const QModelIndex & )), this, SLOT(onCellDblClicked(const QModelIndex&)));

    connect(ui.pushButtonSave, SIGNAL(clicked()), this, SLOT(SlotSaveFile()));
SlotOpenFile();

///connect(ui.pushButtonSave, SIGNAL(clicked()), this, SLOT(SlotSaveFile()));

}

void tbl_dlg::onCellDblClicked(const QModelIndex& index) {
   qDebug() << "onCellDblClicked" << index.column() << index.row();
   if (index.column() == 6) {
       QString tstr = tblModel->data(index).toString();
       if (tstr == "Off") {
          /// tblModel->item()
           qDebug() << "Off"<< tstr;
       }
       else {
           qDebug() << "On" << tstr;

       }

        }

///    qDebug() << "Cell clicked at row:" << row << ", column:" << column;
    // You can now access the item at this position
 ///   QTableWidgetItem* item = tableWidget->item(row, column);
  ///  if (item) {
  ///      qDebug() << "The text in this cell is:" << item->text();
 ///   }
}
void tbl_dlg::onCellClicked(const QModelIndex& index) {
    qDebug() << "onCellClicked";

    ///    qDebug() << "Cell clicked at row:" << row << ", column:" << column;
        // You can now access the item at this position
     ///   QTableWidgetItem* item = tableWidget->item(row, column);
      ///  if (item) {
      ///      qDebug() << "The text in this cell is:" << item->text();
     ///   }
}

tbl_dlg::~tbl_dlg()
{
    /*
    disconnect(this, SIGNAL(req_rd_dbg(int, dbg_dat_req_t*)), pParent, SLOT(slot_rd_dbg(int, dbg_dat_req_t*)));
    disconnect(this, SIGNAL(req_wr_dbg(int, dbg_dat_req_t*)), pParent, SLOT(slot_wr_dbg(int, dbg_dat_req_t*)));
    disconnect(this, SIGNAL(req_send_can_dbg(can_message_t*)), pParent, SLOT(slot_send_can_dbg(can_message_t*)));
    disconnect(ui.pushButton_send_can, SIGNAL(clicked()), this, SLOT(slot_send_can_msg()));
*/
}

void tbl_dlg::SlotSaveFile()
{
  element_data_t t_elem_data;
  QFile file(fileName_tbl);
  if (!file.open(QIODevice::WriteOnly)) {
      QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
      return;
  }
   int cnt_el=p_sn_data->elements.count();
  qDebug() << "cnt_el= " << cnt_el;
  for (int ii = 0; ii < cnt_el; ii++) {
      file.write( (const char*) &t_elem_data,sizeof(element_data_t));
  }
file.close();
}

#define MAX_NUM_ELEM 1000000
void tbl_dlg::SlotOpenFile()
{
    quint32 num_comp = 0;
    element_data_t t_elem_data;

    float min_x=0;
    float min_y=0;
    float max_x=0;
    float max_y=0;
    int num_el = 0;

    int rez = 0;
    tblModel = new QStandardItemModel(this);
    tblModel->setColumnCount(TBL_NUM_COL);   ///
    ui.tableView->setModel(tblModel); // Устанавливаем модель в таблицу
  
     fileName_tbl = QFileDialog::getOpenFileName(this, tr("Open File"), "",
        tr("Tbl Files (*.tbl )"));
      if (fileName_tbl != "") {
        QFile file(fileName_tbl);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
    /// QTextStream in(&file);
        p_sn_data->elements.clear();
        QModelIndex index = tblModel->index(0, 0);

     QStringList head_list;
     head_list << "RefDef" << "PatternName" << "Layer" << "LocationX" << "LocationY" << "Rotation" << "Check";
     tblModel->setHorizontalHeaderLabels(head_list);
     QString item;
     for (int ii=0;ii< MAX_NUM_ELEM;ii++) {
         QList<QStandardItem*> standardItemsList;

         rez = file.read((char*)&t_elem_data, sizeof(element_data_t));
         if (rez <= 0)
             break;
         p_sn_data->elements << t_elem_data;
         item = QString(t_elem_data.RefDes);
         standardItemsList.append(new QStandardItem(item));
         item = QString(t_elem_data.PatternName);
         standardItemsList.append(new QStandardItem(item));
         item = (t_elem_data.Layer)? QString("Botton"):QString("Top");
         standardItemsList.append(new QStandardItem(item));
         item = QString::number(t_elem_data.cvs_pos.LocationX, 'f', 2);
         standardItemsList.append(new QStandardItem(item));
         item = QString::number(t_elem_data.cvs_pos.LocationY, 'f', 2);
         standardItemsList.append(new QStandardItem(item));
         item = QString::number(t_elem_data.cvs_pos.Rotation, 'f', 1);
         standardItemsList.append(new QStandardItem(item));
         item = (t_elem_data.check) ? QString("On") : QString("Off");
         standardItemsList.append(new QStandardItem(item));

         if (min_x > t_elem_data.cvs_pos.LocationX)
             min_x = t_elem_data.cvs_pos.LocationX;
         if(min_y > t_elem_data.cvs_pos.LocationY)
             min_y = t_elem_data.cvs_pos.LocationY;
         if(max_x < t_elem_data.cvs_pos.LocationX)
             max_x = t_elem_data.cvs_pos.LocationX;
         if (max_y < t_elem_data.cvs_pos.LocationY)
             max_y = t_elem_data.cvs_pos.LocationY;

         tblModel->insertRow(tblModel->rowCount(), standardItemsList);
         num_el++;
     }
     p_sn_data->max_x = max_x;
     p_sn_data->max_y = max_y;
     p_sn_data->min_x = min_x;
     p_sn_data->min_y = min_y;
     p_sn_data->num_elem = num_el;
     file.close();
    }
}