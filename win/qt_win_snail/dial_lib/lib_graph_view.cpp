#include "lib_graph_view.h"

LibGraphicView::LibGraphicView(QWidget* parent)
    : QGraphicsView(parent)
{

#if 0
  ///  this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 
 ///   this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // 
    this->setAlignment(Qt::AlignCenter);                        // 
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    // 

     this->setMinimumHeight(100);
    this->setMinimumWidth(100);

    scene = new QGraphicsScene();   // 
    this->setScene(scene);          // 

    group_1 = new QGraphicsItemGroup(); // 
    group_2 = new QGraphicsItemGroup(); // 

    scene->addItem(group_1);            // 
    scene->addItem(group_2);            // 

    timer = new QTimer();               //
    timer->setSingleShot(true);
    //=========================================
    connect(timer, SIGNAL(timeout()), this, SLOT(slotAlarmTimer()));
    timer->start(50);                   // 
#endif
}

LibGraphicView::~LibGraphicView()
{

}
#if 0
void LibGraphicView::slotAlarmTimer()
{
    /* Удаляем все элементы со сцены,
     * если они есть перед новой отрисовкой
     * */
    this->deleteItemsFromGroup(group_1);
    this->deleteItemsFromGroup(group_2);

    int width = this->width();      // определяем ширину нашего виджета
    int height = this->height();    // определяем высоту нашего виджета

    /* Устанавливаем размер сцены по размеру виджета
     * Первая координата - это левый верхний угол,
     * а Вторая - это правый нижний угол
     * */
    scene->setSceneRect(0, 0, width, height);

    /* Приступаем к отрисовке произвольной картинки
     * */
    QPen penBlack(Qt::black); // Задаём чёрную кисть
    QPen penRed(Qt::red);   // Задаём красную кисть

    /* Нарисуем черный прямоугольник
     * */
    group_1->addToGroup(scene->addLine(20, 20, width - 20, 20, penBlack));
    group_1->addToGroup(scene->addLine(width - 20, 20, width - 20, height - 20, penBlack));
    group_1->addToGroup(scene->addLine(width - 20, height - 20, 20, height - 20, penBlack));
    group_1->addToGroup(scene->addLine(20, height - 20, 20, 20, penBlack));

    /* Нарисуем красный квадрат
     * */
    int sideOfSquare = (height > width) ? (width - 60) : (height - 60);
    int centerOfWidget_X = width / 2;
    int centerOfWidget_Y = height / 2;

    group_2->addToGroup(scene->addLine(centerOfWidget_X - (sideOfSquare / 2),
        centerOfWidget_Y - (sideOfSquare / 2),
        centerOfWidget_X + (sideOfSquare / 2),
        centerOfWidget_Y - (sideOfSquare / 2),
        penRed));

    group_2->addToGroup(scene->addLine(centerOfWidget_X + (sideOfSquare / 2),
        centerOfWidget_Y - (sideOfSquare / 2),
        centerOfWidget_X + (sideOfSquare / 2),
        centerOfWidget_Y + (sideOfSquare / 2),
        penRed));

    group_2->addToGroup(scene->addLine(centerOfWidget_X + (sideOfSquare / 2),
        centerOfWidget_Y + (sideOfSquare / 2),
        centerOfWidget_X - (sideOfSquare / 2),
        centerOfWidget_Y + (sideOfSquare / 2),
        penRed));

    group_2->addToGroup(scene->addLine(centerOfWidget_X - (sideOfSquare / 2),
        centerOfWidget_Y + (sideOfSquare / 2),
        centerOfWidget_X - (sideOfSquare / 2),
        centerOfWidget_Y - (sideOfSquare / 2),
        penRed));
}
#endif
void LibGraphicView::resizeEvent(QResizeEvent* event)
{
 ////   timer->start(50);   // Как только событие произошло стартуем таймер для отрисовки
    QGraphicsView::resizeEvent(event);  // Запускаем событие родителького класса
}

#if 0
/* Метод для удаления всех элементов из группы
 * */
void LibGraphicView::deleteItemsFromGroup(QGraphicsItemGroup* group)
{
    /* Перебираем все элементы сцены, и если они принадлежат группе,
     * переданной в метод, то удаляем их
     * */
    foreach(QGraphicsItem * item, scene->items(group->boundingRect())) {
        if (item->group() == group) {
            delete item;
        }
    }
}
#endif
void LibGraphicView::wheelEvent(QWheelEvent* event) {
    if (event->modifiers() == Qt::ShiftModifier) {
        int cur_angle = event->angleDelta().y();
        qreal scaleFactor = (cur_angle > 0) ? 1.2 : 1.0 / 1.2;
    ///   qreal scaleFactorY = (event->angleDelta().y() > 0) ? 1.2 : 1.0 / 1.2;
       scale(scaleFactor, scaleFactor);
       double currentScale = transform().m11();
       emit zoom_chnged(currentScale);
     }
    else
      QGraphicsView::wheelEvent(event);
}

void LibGraphicView::enterEvent(QEvent* event)
{
    QGraphicsView::enterEvent(event);
    viewport()->setCursor(Qt::CrossCursor);
}

void LibGraphicView::mouseReleaseEvent(QMouseEvent* event)
{
    QGraphicsView::mouseReleaseEvent(event);
    viewport()->setCursor(Qt::CrossCursor);
}
