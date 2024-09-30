#include "itemSettings.h"
#include "ui_itemSettings.h"
#include <QColorDialog>
#include <QBrush>
#include <QPen>
#include <QDebug>
////#include "verectangle.h"

item_Settings::item_Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemSettings)///,
    ///currentItem(nullptr)
{
    ui->setupUi(this);
    ui->BGcolor->setVisible(false);
    ui->BorderColor->setVisible(false);
    ui->labelBGColor->setVisible(false);
    ui->labelBorderColor->setVisible(false);
    ui->labelBorderThick->setVisible(false);
    ui->labelHight->setVisible(false);
    ui->labelWidth->setVisible(false);
    setBorderColor(Qt::black);
    setBGColor(Qt::white);
    setBorderThick(1);
    setitemWidth(100);
    setitemHeight(20);

 
    connect(ui->BGcolor, &ColorLabel::clicked,
            [=](){
        QColorDialog dialog;
        connect(&dialog, &QColorDialog::colorSelected, this, &item_Settings::setBGColor);
        dialog.exec();
    });
#if 1
    connect(ui->BorderColor, &ColorLabel::clicked,
            [=](){
        QColorDialog dialog;
        connect(&dialog, &QColorDialog::colorSelected, this, &item_Settings::setBorderColor);
        dialog.exec();
    });

 ///   connect(ui->comboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
  ////          this, &VERectangleSettings::comboBoxIndexChanged);
 ///   connect(ui->borderWidth, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
  ////          this, &VERectangleSettings::setBorderWidth);
#endif
}

item_Settings::~item_Settings()
{
    delete ui;
 ///   delete currentItem;
}

QColor item_Settings::BGcolor() const
{
    return m_BGcolor;
}

QColor item_Settings::borderColor() const
{
    return m_borderColor;
}

quint8 item_Settings::borderThick() const
{
    return m_borderThick;
}
quint16 item_Settings::itemWidth() const
{
    return m_width;

}
quint16 item_Settings::itemHeight() const
{
    return m_height;
}

en_item_type item_Settings::itemType() const
{
    return item_type;
}

void item_Settings::setBGColor(const QColor &color)
{

m_BGcolor = color;
ui->BGcolor->setColor(color);
#if 0
if(currentItem != nullptr){
    currentItem->setBrush(QBrush(m_BGcolor));
     }
#endif
emit BGcolorChanged(m_BGcolor);
}


void item_Settings::setBorderColor(const QColor &color)
{
    m_borderColor = color;
    ui->BorderColor->setColor(color);
#if 0
    if(currentItem != nullptr){
        QPen pen(color,currentItem->pen().width());
        currentItem->setPen(pen);
    }
#endif
    emit borderColorChanged(m_borderColor);
}

void item_Settings::setBorderThick(const quint8& thick)
{
    m_borderThick = thick;
#if 0
    if(currentItem != nullptr){
        if(thick == 0){
            currentItem->setPen(Qt::NoPen);
        } else {
            QPen pen(currentItem->pen().color(), thick);
            currentItem->setPen(pen);
        }
    }
#endif
    emit borderThickChanged(m_borderThick);
}
void item_Settings::setitemWidth(const quint16& width)
{
m_width= width;
 
}
void item_Settings::setitemHeight(const quint16& height)
{
 m_height= height;

}
void item_Settings::setitemType(const en_item_type& type)
{
    item_type = type;
}

#if 0
void item_Settings::newRectangle(VERectangle *rect)
{
#if 0
    if(ui->comboBox->currentIndex() == 0){
        rect->setBrush(QBrush(m_color_1));
    } else {
        setGradient(rect);
    }
    if(m_borderWidth == 0){
        rect->setPen(Qt::NoPen);
    } else {
        rect->setPen(QPen(m_borderColor, m_borderWidth));
    }
#endif
}

void item_Settings::loadRectangle(VERectangle *rect)
{
#if 0
    currentRectangle = rect;

    m_color_1 = currentRectangle->brush().color();
    m_borderColor = currentRectangle->pen().color();
    if(currentRectangle->pen().style() == Qt::NoPen){
        m_borderWidth = 0;
    } else {
        m_borderWidth = currentRectangle->pen().width();
    }
    ui->color_1->setColor(m_color_1);
    ui->borderColor->setColor(m_borderColor);
    ui->borderWidth->setValue(m_borderWidth);
#endif
}
#endif
void item_Settings::deselect()
{
 ////   currentItem = nullptr;
}

void item_Settings::setVisible(bool visible)
{
    switch (item_type)
    {
    case RECT_TYPE:
        ui->BGcolor->setVisible(false);
        ui->BorderColor->setVisible(visible);
        ui->labelBorderColor->setVisible(visible);
        ui->labelBorderThick->setVisible(visible);
        ui->labelHight->setVisible(visible);
        ui->labelWidth->setVisible(visible);
        ui->item_border_thick->setVisible(visible);
        ui->item_height->setVisible(visible);
        ui->item_width->setVisible(visible);
        ui->item_width->show();
        break;
    case FRECT_TYPE:
        ui->BGcolor->setVisible(visible);
        ui->BorderColor->setVisible(visible);
        ui->labelBGColor->setVisible(visible);
        ui->labelBorderColor->setVisible(visible);
        ui->labelBorderThick->setVisible(visible);
        ui->labelHight->setVisible(visible);
        ui->labelWidth->setVisible(visible);
        ui->item_border_thick->setVisible(visible);
        ui->item_height->setVisible(visible);
        ui->item_width->setVisible(visible);
        break;
    case VLINE_TYPE:
        ui->BGcolor->setVisible(false);
        ui->BorderColor->setVisible(visible);
        ui->labelBGColor->setVisible(false);
        ui->labelBorderColor->setVisible(visible);
        ui->labelBorderThick->setVisible(visible);
        ui->labelHight->setVisible(visible);
        ui->item_height->setVisible(visible);
        ui->labelWidth->setVisible(false);
        ui->item_border_thick->setVisible(visible);
        break;
    case HLINE_TYPE:
        ui->BGcolor->setVisible(false);
        ui->BorderColor->setVisible(visible);
        ui->labelBGColor->setVisible(false);
        ui->labelBorderColor->setVisible(visible);
        ui->labelBorderThick->setVisible(visible);
        ui->labelHight->setVisible(false);
        ui->labelWidth->setVisible(visible);
        ui->item_border_thick->setVisible(visible);
        ui->item_width->setVisible(visible);
        break;
    case CIRCLE_TYPE:
        ui->BGcolor->setVisible(visible);
        ui->BorderColor->setVisible(visible);
        ui->labelBGColor->setVisible(visible);
        ui->labelBorderColor->setVisible(visible);
        ui->labelBorderThick->setVisible(visible);
        ui->labelHight->setVisible(visible);
        ui->labelWidth->setVisible(visible);
        ui->item_border_thick->setVisible(visible);
        break;

    }
}


