#include "dial_lib.h"
#include <QSvgGenerator>
#include <QFileDialog>
#include <QDebug>
#include <QGraphicsItem>
#include <QMessageBox>
#include "svgreader.h"
///#include "veworkplace.h"
///#include "vepolyline.h"
#include "cust_rect.h"
#include "cust_line.h"
#include "cust_circle.h"
#include "params.h"

DialLib::DialLib(QWidget *parent):
    QDialog(parent, Qt::Window),pParent(parent)
   , ui(), cur_rej(REJ_SELECT), cur_item(FRECT_TYPE)
{
	ui.setupUi(this);
    ui.BorderColor->setColor(params::LibItemBrdColor);
    ui.BGcolor->setColor(params::LibItemBGColor);
    connect(ui.BorderColor, &ColorLabel::clicked,
        [=]() {
            QColorDialog dialog;
            connect(&dialog, &QColorDialog::colorSelected, this, &DialLib::setBorderColor);
            dialog.exec();
        });
    connect(ui.BGcolor, &ColorLabel::clicked,
        [=]() {
            QColorDialog dialog;
            connect(&dialog, &QColorDialog::colorSelected, this, &DialLib::setBGColor);
            dialog.exec();
        });

///===========================================================
 ///   libView =(LibGraphicView*)ui.graphicsView;
    ui.item_border_thick->set_num_dig(2);
    ui.item_border_thick->set_data(reinterpret_cast<quint8*>(&params::LibItemBrdThick));
    ui.item_border_thick->set_min_max(1, 10);
    ui.item_border_thick->show_par();

    ui.item_width->set_num_dig(3);
    ui.item_width->set_data(reinterpret_cast<quint8*>(&params::LibItemWidth ));
    ui.item_width->set_min_max(1, 999);
    ui.item_width->show_par();

    ui.item_height->set_num_dig(3);
    ui.item_height->set_data(reinterpret_cast<quint8*>(&params::LibItemHeight ));
    ui.item_height->set_min_max(1, 999);
    ui.item_height->show_par();

///===========================================================

    scene = new LibPaintScene(this,&cur_item, &cur_rej);       // 
    scene->setItemIndexMethod(QGraphicsScene::NoIndex); ///???
 
    ui.graphicsView->setScene(scene);  // 
    ui.graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui.graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
   /// GraphicsView->setStyleSheet("background: transparent;border:0px");
    ui.graphicsView->setStyleSheet("background: transparent;border:0px");

    ////ui.graphicsView->setCursor(QCursor());

    scene->setSceneRect(0, 0, 2000, 2000); //


    timer = new QTimer();       // 
    connect(timer, &QTimer::timeout, this, &DialLib::slotTimer);
    timer->start(100);          // 

    ui.comboBox_item->addItem("Rect", RECT_TYPE);
	ui.comboBox_item->addItem("FRect", FRECT_TYPE);
	ui.comboBox_item->addItem("VLine", VLINE_TYPE);
    ui.comboBox_item->addItem("HLine", HLINE_TYPE);
    ui.comboBox_item->addItem("Circle", CIRCLE_TYPE);
    ui.comboBox_item->addItem("Point", POINT_TYPE);

    connect(ui.butt_select, SIGNAL(clicked()), this, SLOT(on_butt_select()));
    connect(ui.butt_place, SIGNAL(clicked()), this, SLOT(on_butt_place()));
    connect(ui.comboBox_item, SIGNAL(currentIndexChanged(int)), this, SLOT(indexChanged(int)));
    show_rej();
    show_params();

 ///    ui.rectangleSettings->setVisible(false);
 ///   ui.polylineSettings->setVisible(false);

 ///   connect(ui.butLine, &QToolButton::clicked, [=]() {scene->setCurrentAction(HLineType); });
  ///  connect(ui.butRectangle, &QToolButton::clicked, [=]() {scene->setCurrentAction(RectangleType); });
 ///   connect(ui.butDefault, &QToolButton::clicked, [=]() {scene->setCurrentAction(DefaultType); });

    connect(scene, &LibPaintScene::selectionChanged, this, &DialLib::checkSelection);
    connect(scene, &LibPaintScene::currentActionChanged, this, &DialLib::checkActionStates);
    connect(scene, &LibPaintScene::signalSelectItem, this, &DialLib::selectItem);
    connect(scene, &LibPaintScene::signalNewSelectItem, this, &DialLib::selectNewItem);
    connect(ui.zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(on_zoom_changed(int)));
    connect(ui.graphicsView, SIGNAL(zoom_chnged(double)), this, SLOT(sl_zoom_changed(double)));
///=======================================
    
    connect(ui.pushButton_grid, SIGNAL(clicked()), this, SLOT(on_grid()));
 
    connect(scene, &LibPaintScene::signalPress, this, &DialLib::slShowBeg);
    connect(scene, &LibPaintScene::signalMove, this, &DialLib::slShowEnd);
    connect(ui.butt_clr, SIGNAL(clicked()), this, SLOT(on_clr()));
///===================================================================
    
    QScriptValue inputVal = m_engine.newQObject(ui.edInput);
    m_engine.globalObject().setProperty("input", inputVal);

    QScriptValue outputVal = m_engine.newQObject(ui.edOutput);
    m_engine.globalObject().setProperty("output", outputVal);

    connect(ui.ButtLoad, SIGNAL(clicked()), this, SLOT(loadScript()));
    connect(ui.ButtRun, SIGNAL(clicked()), this, SLOT(runScript()));


}

DialLib::~DialLib()
{
  ////  disconnect(this, SIGNAL(req_rd_dbg(int, dbg_dat_req_t*)), pParent, SLOT(slot_rd_dbg(int, dbg_dat_req_t*)));
 ////   disconnect(this, SIGNAL(req_wr_dbg(int, dbg_dat_req_t*)), pParent, SLOT(slot_wr_dbg(int, dbg_dat_req_t*)));
 ///   disconnect(this, SIGNAL(req_send_can_dbg(can_message_t*)), pParent, SLOT(slot_send_can_dbg(can_message_t*)));
 ///   disconnect(ui.pushButton_send_can, SIGNAL(clicked()), this, SLOT(slot_send_can_msg()));

}
///connect(ui.butt_select, SIGNAL(clicked()), this, SLOT(on_butt_select()));
////connect(ui.butt_place, SIGNAL(clicked()), this, SLOT(on_butt_place()));
void  DialLib::show_rej()
{
    if (cur_rej == REJ_SELECT)
    {
        ui.butt_select->setStyleSheet("background-color: green;");
        ui.butt_place->setStyleSheet(" ");
}
    else if (cur_rej == REJ_PLACE)
    {
        ui.butt_select->setStyleSheet("");
        ui.butt_place->setStyleSheet("background-color: green; ");
    }

}
void  DialLib::on_grid()
{
    if (scene->on_background)
        scene->on_background = false;
    else
        scene->on_background = true;

 scene->update();
 }
void  DialLib::on_butt_select()
{
    scene->setCurrentAction(_DefaultType);
    cur_rej = REJ_SELECT;
    show_rej();
    ui.comboBox_item->setVisible(false);
    show_params();

 ///   ui.itemSettings->setVisible(false);

}
void  DialLib::show_params()
{
if (cur_rej == REJ_SELECT)
    {
    ui.labelBGColor->setVisible(false);
    ui.BGcolor->setVisible(false);
    ui.BorderColor->setVisible(false);
    ui.labelBorderColor->setVisible(false);
    ui.labelBorderThick->setVisible(false);
    ui.labelHight->setVisible(false);
    ui.labelWidth->setVisible(false);
    ui.item_border_thick->setVisible(false);
    ui.item_height->setVisible(false);
    ui.item_width->setVisible(false);
    ui.label_with->setVisible(false);
    ui.label_hight->setVisible(false);

    }
 else
    {
    switch (cur_item)
    {
    case RECT_TYPE:
        ui.labelBGColor->setVisible(false);
        ui.BGcolor->setVisible(false);
        ui.BorderColor->setVisible(true);
        ui.labelBorderColor->setVisible(true);
        ui.labelBorderThick->setVisible(true);
        ui.labelHight->setVisible(true);
        ui.labelWidth->setVisible(true);
        ui.item_border_thick->setVisible(true);
        ui.item_height->setVisible(true);
        ui.item_width->setVisible(true);
        ui.label_with->setVisible(true);
        ui.label_hight->setVisible(true);

        break;
    case FRECT_TYPE:
        ui.labelBGColor->setVisible(true);
        ui.BGcolor->setVisible(true);
        ui.BorderColor->setVisible(true);
        ui.labelBorderColor->setVisible(true);
        ui.labelBorderThick->setVisible(true);
        ui.labelHight->setVisible(true);
        ui.labelWidth->setVisible(true);
        ui.item_border_thick->setVisible(true);
        ui.item_height->setVisible(true);
        ui.item_width->setVisible(true);
        ui.label_with->setVisible(true);
        ui.label_hight->setVisible(true);

        break;
    case VLINE_TYPE:
        ui.labelBGColor->setVisible(false);
        ui.BGcolor->setVisible(false);
        ui.BorderColor->setVisible(true);
        ui.labelBorderColor->setVisible(true);
        ui.labelBorderThick->setVisible(true);
        ui.labelHight->setVisible(true);
        ui.labelWidth->setVisible(true);
        ui.item_border_thick->setVisible(true);
        ui.item_height->setVisible(true);
        ui.item_width->setVisible(true);
        ui.label_with->setVisible(true);
        ui.label_hight->setVisible(true);

        break;
    case HLINE_TYPE:
        ui.labelBGColor->setVisible(false);
        ui.BGcolor->setVisible(false);
        ui.BorderColor->setVisible(true);
        ui.labelBorderColor->setVisible(true);
        ui.labelBorderThick->setVisible(true);
        ui.labelHight->setVisible(true);
        ui.labelWidth->setVisible(true);
        ui.item_border_thick->setVisible(true);
        ui.item_height->setVisible(true);
        ui.item_width->setVisible(true);
        ui.label_with->setVisible(true);
        ui.label_hight->setVisible(true);
        break;
    case CIRCLE_TYPE:
        ui.labelBGColor->setVisible(false);
        ui.BGcolor->setVisible(false);
        ui.BorderColor->setVisible(true);
        ui.labelBorderColor->setVisible(true);
        ui.labelBorderThick->setVisible(true);
        ui.labelHight->setVisible(true);
        ui.labelWidth->setVisible(true);
        ui.item_border_thick->setVisible(true);
        ui.item_height->setVisible(true);
        ui.item_width->setVisible(true);
        ui.label_with->setVisible(true);
        ui.label_hight->setVisible(true);
        break;
    case POINT_TYPE:
        ui.labelBGColor->setVisible(false);
        ui.BGcolor->setVisible(false);
        ui.BorderColor->setVisible(true);
        ui.labelBorderColor->setVisible(true);
        ui.labelBorderThick->setVisible(true);
        ui.labelHight->setVisible(true);
        ui.labelWidth->setVisible(true);
        ui.item_border_thick->setVisible(true);
        ui.item_height->setVisible(true);
        ui.item_width->setVisible(true);
        ui.label_with->setVisible(true);
        ui.label_hight->setVisible(true);
        break;
    }
}
}
void  DialLib::on_butt_place()
{
    cur_rej = REJ_PLACE;
    ui.comboBox_item->setVisible(true);
    show_rej();
    show_params();

 ///   ui.itemSettings->setitemType(cur_item);
 ///   ui.itemSettings->setVisible(true);

    switch (cur_item)
    {
    case RECT_TYPE:
        scene->setCurrentAction(RectangleType);
        break;
    case VLINE_TYPE:
        scene->setCurrentAction(VLineType);
        break;
    case HLINE_TYPE:
        scene->setCurrentAction(HLineType);
        break;

    }

}


void DialLib::on_clr()
{
scene->clear();
scene->update();
  ////  ui.textEdit_rd_dat->clear();
}
void DialLib::SlotTest()
{
 emit SignalTest();
}
///============================================
///===========================================
void DialLib::slotTimer()
{
     timer->stop();
 ///   scene->setSceneRect(0, 0, ui.graphicsView->width() - 20, ui.graphicsView->height() - 20);
}

void DialLib::resizeEvent(QResizeEvent* event)
{
    timer->start(100);
    QWidget::resizeEvent(event);
}
void DialLib::sl_zoom_changed(double value)
{
///double currentScale = uitransform().m11();
///    qDebug() << "zoom changed:" << value;
///ui.lineEdit_zoom->setText(QString::number(value));
}

void DialLib::on_zoom_changed(int value)
{
#if 0
    hid_cmd_t t_cmd;
    t_cmd.cmd = CMD_SET_LED0;
    t_cmd.num_bytes = 2;
    t_cmd.dat[0] = value & 0xff;
    t_cmd.dat[1] = (value >> 8) & 0xff;

    ///   int value = ui->lightSlider->value();
    qDebug() << "on_value_led0_changed" << value << t_cmd.dat[0] << t_cmd.dat[1];

    put_hid_cmd(&t_cmd);
#endif
}


void DialLib::indexChanged(int index)
{
 cur_item = (en_item_type)ui.comboBox_item->currentIndex();
 show_params();

 ///ui.itemSettings->setitemType(cur_item);
 ///ui.itemSettings->setVisible(true);

 switch (cur_item)
 {
 case RECT_TYPE:
     scene->setCurrentAction(RectangleType);
     break;
 case VLINE_TYPE:
     scene->setCurrentAction(VLineType);
     break;
 case HLINE_TYPE:
     scene->setCurrentAction(HLineType);
     break;

 }

    // Do something here on ComboBox index change
}
///void DialLib::mousePressEvent(QGraphicsSceneMouseEvent* event)
///{
  ///  QGraphicsScene::mousePressEvent(event);
///================================================================
void DialLib::checkSelection()
{
    checkActionStates();
#if 1
    switch (scene->selectedItems().length()) {
    case 0:
        ///ui.rectangleSettings->deselect();
        ///ui.polylineSettings->deselect();
        checkActionStates();
     ///   ui.toolsWidget->setEnabled(true);
        break;
    case 1:
        switch (scene->selectedItems().at(0)->type()) {
        case QGraphicsRectItem::Type: {
            ///ui.rectangleSettings->setVisible(true);
            ///ui.polylineSettings->deselect();
            ///ui.polylineSettings->setVisible(false);
            break;
        }
        default: {
           /// ui.rectangleSettings->deselect();
            ///ui.rectangleSettings->setVisible(false);
            ///ui.polylineSettings->setVisible(true);
            break;
        }
        }
        checkActionStates();
///        ui.toolsWidget->setEnabled(true);
        break;
    default:
       /// ui.rectangleSettings->deselect();
       /// ui.polylineSettings->deselect();
       /// ui.toolsWidget->setEnabled(false);
        break;
    }
#endif
}
void DialLib::checkActionStates()
{
#if 0
    ui.graphicsView->setDragMode(QGraphicsView::NoDrag);
  ///  ui.rectangleSettings->setVisible(false);
////    ui.polylineSettings->setVisible(false);
    switch (scene->currentAction()) {
    case HLineType:
  ///     ui.itemSettings->setVisible(true);
        break;
    case VLineType:
     ///   ui.polylineSettings->setVisible(true);
        break;
    case RectangleType:
    ///    ui.rectangleSettings->setVisible(true);
        break;
    case CircleType:
 ///       ui.rectangleSettings->setVisible(true);
        break;
    case SelectionType:
        break;
    default:
        ui.graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
        break;
    }
#endif
}
void DialLib::selectItem(QGraphicsItem* item)
{
    switch (item->type()) {
    case QGraphicsRectItem::Type: {
 ///       VERectangle* rect = qgraphicsitem_cast<VERectangle*>(item);
 ///       ui.rectangleSettings->loadRectangle(rect);
        break;
    }
    case QGraphicsPathItem::Type: {
  ///      VEPolyline* polyline = qgraphicsitem_cast<VEPolyline*>(item);
 ///       ui.polylineSettings->loadPolyline(polyline);
        break;
    }
    default:
        break;
    }
}

void DialLib::selectNewItem(QGraphicsItem* item)
{
    switch (item->type()) {
    case QGraphicsRectItem::Type: {
  ///      VERectangle* rect = qgraphicsitem_cast<VERectangle*>(item);
  ///      ui.rectangleSettings->newRectangle(rect);
        break;
    }
    case QGraphicsPathItem::Type: {
  ///      VEPolyline* polyline = qgraphicsitem_cast<VEPolyline*>(item);
  ///      ui.polylineSettings->newPolyline(polyline);
        break;
    }
    default:
        break;
    }
}

void DialLib::on_butSave_clicked()
{
    QString newPath = QFileDialog::getSaveFileName(this, tr("Save SVG"),
        path, tr("SVG files (*.svg)"));

    if (newPath.isEmpty())
        return;

    path = newPath;

    QSvgGenerator generator;
    generator.setFileName(path);
    generator.setSize(QSize(scene->width(), scene->height()));
    generator.setViewBox(QRect(0, 0, scene->width(), scene->height()));
    generator.setTitle(tr("Lib Editor"));
    generator.setDescription(tr("File created by Snail lib Editor."));

    QPainter painter;
    painter.begin(&generator);
    scene->render(&painter);
    painter.end();
}

void DialLib::on_butOpen_clicked()
{
    QString newPath = QFileDialog::getOpenFileName(this, tr("Open SVG"),
        path, tr("SVG files (*.svg)"));
    if (newPath.isEmpty())
        return;

    path = newPath;
    scene->clear();

    scene->setSceneRect(SvgReader::getSizes(path));

    foreach(QGraphicsItem * item, SvgReader::getElements(path)) {
        qDebug() << "item->type=" << item->type();
        switch (item->type()) {
          case QGraphicsPathItem::Type: {
            cust_line* polyline = qgraphicsitem_cast<cust_line*>(item);
            scene->addItem(polyline);
            connect(polyline, &cust_line::signalPress, scene, &LibPaintScene::signalSelectItem);
            connect(polyline, &cust_line::signalMove, scene, &LibPaintScene::slotMove);
            break;
        }
/*
        case QGraphicsLineItem::Type: {
            cust_line* line = qgraphicsitem_cast<cust_line*>(item);
            scene->addItem(line);
            connect(line, &cust_line::clicked, scene, &LibPaintScene::signalSelectItem);
            connect(line, &cust_line::signalMove, scene, &LibPaintScene::slotMove);
            break;
        }
*/
        case QGraphicsEllipseItem::Type: {
            cust_circle* circle = qgraphicsitem_cast<cust_circle*>(item);
            scene->addItem(circle);
            connect(circle, &cust_circle::clicked, scene, &LibPaintScene::signalSelectItem);
            connect(circle, &cust_circle::signalMove, scene, &LibPaintScene::slotMove);
            break;
        }
        case QGraphicsRectItem::Type: {
            cust_rect* rect = qgraphicsitem_cast<cust_rect*>(item);
            scene->addItem(rect);
            connect(rect, &cust_rect::clicked, scene, &LibPaintScene::signalSelectItem);
            connect(rect, &cust_rect::signalMove, scene, &LibPaintScene::slotMove);
            break;
        }
        default:
            break;
        }
    }
    scene->update();
}
///====================================================================
void DialLib::setBGColor(const QColor& color)
{
 ///   m_BGcolor = color;
 ui.BGcolor->setColor(color);
 params::LibItemBGColor = color;
 ////   emit BGcolorChanged(m_BGcolor);
}
void DialLib::setBorderColor(const QColor& color)
{
///    m_borderColor = color;
 ui.BorderColor->setColor(color);
 params::LibItemBrdColor = color;
 ///emit borderColorChanged(m_borderColor);
}
void DialLib::slShowBeg(QPointF pnt)
{
ui.lab_bx->setText(QString("bx=%1").arg(pnt.x()));
ui.lab_by->setText(QString("by=%1").arg(pnt.y()));
}
void DialLib::slShowEnd(QPointF pnt)
{
ui.lab_dx->setText(QString("dx=%1").arg(pnt.x()));
ui.lab_dy->setText(QString("dy=%1").arg(pnt.y()));
}
///=============================================================
#if 0
void DialLib::on_butOpen_clicked()
{
    QString newPath = QFileDialog::getOpenFileName(this, tr("Open SVG"),
        path, tr("SVG files (*.svg)"));
    if (newPath.isEmpty())
        return;

    path = newPath;
#endif
void DialLib::loadScript() {
QString newPath = QFileDialog::getOpenFileName(this, tr("Open Script"),
                   path_script, tr("Script files (*.js)"));
    if (newPath.isEmpty())
        return;

    path_script = newPath;
    QFile f(path_script);
    if (f.open(QIODevice::ReadOnly)) {
        ui.txtScript->setText(f.readAll());
    }

/*
    QString fileName = "";
    if (ui->rbUpperDemo->isChecked()) {
        fileName = "upper_demo.js";
    }
    else if (ui->rbConnectDemo->isChecked()) {
        fileName = "connect_demo.js";
    }
    else if (ui->rbConnectFuncDemo->isChecked()) {
        fileName = "connect_func_demo.js";
    }

    QFile f(":/" + fileName);
    if (f.open(QIODevice::ReadOnly)) {
        ui->txtScript->setText(f.readAll());
    }
    */
}

void DialLib::runScript() {

    ui.edInput->disconnect();
    ui.edOutput->disconnect();
    ui.edOutput->clear();

    QScriptValue result = m_engine.evaluate(ui.txtScript->toPlainText());
    if (result.isError()) {
        ui.edOutput->setText(result.toString());
    }
 
}