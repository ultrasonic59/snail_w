#include "dial_lib.h"
#include <QSvgGenerator>
#include <QFileDialog>
#include <QDebug>
#include <QGraphicsItem>
#include <QMessageBox>
#include "svgreader.h"
///#include "veworkplace.h"
#include "vepolyline.h"
#include "verectangle.h"


DialLib::DialLib(QWidget *parent, PlotProperties* Plot_Prop):
    QDialog(parent, Qt::Window),pParent(parent),pPlot_Prop(Plot_Prop)
   , ui(), cur_rej(REJ_SELECT), cur_item(RECT_TYPE)
{
	ui.setupUi(this);
    scene = new LibPaintScene(this,pPlot_Prop,&cur_item, &cur_rej);       // 
    scene->setItemIndexMethod(QGraphicsScene::NoIndex); ///???

    ui.graphicsView->setScene(scene);  // 
    ui.graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui.graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui.graphicsView->setCursor(QCursor());

    scene->setSceneRect(0, 0, 2000, 2000); //


    timer = new QTimer();       // 
    connect(timer, &QTimer::timeout, this, &DialLib::slotTimer);
    timer->start(100);          // 

    ui.comboBox_item->addItem("Rect", RECT_TYPE);
	ui.comboBox_item->addItem("FRect", FRECT_TYPE);
	ui.comboBox_item->addItem("VLine", VLINE_TYPE);
    ui.comboBox_item->addItem("HLine", HLINE_TYPE);
    ui.comboBox_item->addItem("Circle", CIRCLE_TYPE);

    connect(ui.butt_select, SIGNAL(clicked()), this, SLOT(on_butt_select()));
    connect(ui.butt_place, SIGNAL(clicked()), this, SLOT(on_butt_place()));
    connect(ui.comboBox_item, SIGNAL(currentIndexChanged(int)), this, SLOT(indexChanged(int)));
    show_rej();

    ui.itemSettings->setVisible(true);
    ui.rectangleSettings->setVisible(false);
    ui.polylineSettings->setVisible(false);

    connect(ui.butLine, &QToolButton::clicked, [=]() {scene->setCurrentAction(HLineType); });
    connect(ui.butRectangle, &QToolButton::clicked, [=]() {scene->setCurrentAction(RectangleType); });
 ///   connect(ui.butDefault, &QToolButton::clicked, [=]() {scene->setCurrentAction(DefaultType); });

    connect(scene, &LibPaintScene::selectionChanged, this, &DialLib::checkSelection);
    connect(scene, &LibPaintScene::currentActionChanged, this, &DialLib::checkActionStates);
    connect(scene, &LibPaintScene::signalSelectItem, this, &DialLib::selectItem);
    connect(scene, &LibPaintScene::signalNewSelectItem, this, &DialLib::selectNewItem);
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
void  DialLib::on_butt_select()
{
    scene->setCurrentAction(_DefaultType);
    cur_rej = REJ_SELECT;
    show_rej();
}

void  DialLib::on_butt_place()
{
    cur_rej = REJ_PLACE;
    show_rej();
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


void DialLib::clear_textEdit()
{
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
void DialLib::indexChanged(int index)
{
 cur_item = (en_item_tipe)ui.comboBox_item->currentIndex();
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
        ui.rectangleSettings->deselect();
        ui.polylineSettings->deselect();
        checkActionStates();
        ui.toolsWidget->setEnabled(true);
        break;
    case 1:
        switch (scene->selectedItems().at(0)->type()) {
        case QGraphicsRectItem::Type: {
            ui.rectangleSettings->setVisible(true);
            ui.polylineSettings->deselect();
            ui.polylineSettings->setVisible(false);
            break;
        }
        default: {
            ui.rectangleSettings->deselect();
            ui.rectangleSettings->setVisible(false);
            ui.polylineSettings->setVisible(true);
            break;
        }
        }
        checkActionStates();
        ui.toolsWidget->setEnabled(true);
        break;
    default:
        ui.rectangleSettings->deselect();
        ui.polylineSettings->deselect();
        ui.toolsWidget->setEnabled(false);
        break;
    }
#endif
}
void DialLib::checkActionStates()
{
#if 1
    ui.graphicsView->setDragMode(QGraphicsView::NoDrag);
    ui.rectangleSettings->setVisible(false);
    ui.polylineSettings->setVisible(false);
    switch (scene->currentAction()) {
    case HLineType:
       ui.itemSettings->setVisible(true);
        break;
    case VLineType:
        ui.polylineSettings->setVisible(true);
        break;
    case RectangleType:
        ui.rectangleSettings->setVisible(true);
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
        VERectangle* rect = qgraphicsitem_cast<VERectangle*>(item);
        ui.rectangleSettings->loadRectangle(rect);
        break;
    }
    case QGraphicsPathItem::Type: {
        VEPolyline* polyline = qgraphicsitem_cast<VEPolyline*>(item);
        ui.polylineSettings->loadPolyline(polyline);
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
        VERectangle* rect = qgraphicsitem_cast<VERectangle*>(item);
        ui.rectangleSettings->newRectangle(rect);
        break;
    }
    case QGraphicsPathItem::Type: {
        VEPolyline* polyline = qgraphicsitem_cast<VEPolyline*>(item);
        ui.polylineSettings->newPolyline(polyline);
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
    generator.setTitle(tr("Vector Editor"));
    generator.setDescription(tr("File created by Vector Editor."));

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
        switch (item->type()) {
        case QGraphicsPathItem::Type: {
            VEPolyline* polyline = qgraphicsitem_cast<VEPolyline*>(item);
            scene->addItem(polyline);
            connect(polyline, &VEPolyline::clicked, scene, &LibPaintScene::signalSelectItem);
            connect(polyline, &VEPolyline::signalMove, scene, &LibPaintScene::slotMove);
            break;
        }
        case QGraphicsRectItem::Type: {
            VERectangle* rect = qgraphicsitem_cast<VERectangle*>(item);
            scene->addItem(rect);
            connect(rect, &VERectangle::clicked, scene, &LibPaintScene::signalSelectItem);
            connect(rect, &VERectangle::signalMove, scene, &LibPaintScene::slotMove);
            break;
        }
        default:
            break;
        }
    }
}
