#include "item_settings.h"
#include "ui_item_settings.h"
#include <QColorDialog>
#include <QBrush>
#include <QPen>
#include <QDebug>
#include "verectangle.h"

itemSettings::itemSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemSettings),
    currentRectangle(nullptr)
{
#if 0
    ui->setupUi(this);
    ui->color_2->setVisible(false);
    ui->labelColor_2->setVisible(false);

    setColor_1(Qt::white);
    setColor_2(Qt::white);
    setBorderColor(Qt::black);
    setBorderWidth(1);

    connect(ui->color_1, &ColorLabel::clicked,
            [=](){
        QColorDialog dialog;
    ///    connect(&dialog, &QColorDialog::colorSelected, this, &VERectangleSettings::setColor_1);
        dialog.exec();
    });
  ////  connect(ui->color_2, &ColorLabel::clicked,
   ////         [=](){
        QColorDialog dialog;
    ///    connect(&dialog, &QColorDialog::colorSelected, this, &VERectangleSettings::setColor_2);
        dialog.exec();
    });
  ///  connect(ui->borderColor, &ColorLabel::clicked,
  ///          [=](){
        QColorDialog dialog;
    ///    connect(&dialog, &QColorDialog::colorSelected, this, &VERectangleSettings::setBorderColor);
        dialog.exec();
    });

 ///   connect(ui->comboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
  ////          this, &VERectangleSettings::comboBoxIndexChanged);
 ///   connect(ui->borderWidth, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
  ////          this, &VERectangleSettings::setBorderWidth);
#endif
}

itemSettings::~itemSettings()
{
    delete ui;
    delete currentRectangle;
}

QColor itemSettings::color_1() const
{
    return m_color_1;
}

QColor itemSettings::color_2() const
{
    return m_color_2;
}

QColor itemSettings::borderColor() const
{
    return m_borderColor;
}

int itemSettings::borderWidth() const
{
    return m_borderWidth;
}

void itemSettings::setColor_1(const QColor &color)
{
#if 0
    m_color_1 = color;
    ui->color_1->setColor(color);
    if(currentRectangle != nullptr){
        if(ui->comboBox->currentIndex() == 0){
            currentRectangle->setBrush(QBrush(m_color_1));
        } else {
             setGradient(currentRectangle);
        }
    }
    emit color_1Changed(m_color_1);
#endif
}

void itemSettings::setColor_2(const QColor &color)
{
#if 0
    m_color_2 = color;
    ui->color_2->setColor(color);
    if(currentRectangle != nullptr){
         setGradient(currentRectangle);
    }
    emit color_2Changed(m_color_2);
#endif
}

void itemSettings::setBorderColor(const QColor &color)
{
#if 0
    m_borderColor = color;
    ui->borderColor->setColor(color);
    if(currentRectangle != nullptr){
        QPen pen(color,currentRectangle->pen().width());
        currentRectangle->setPen(pen);
    }
    emit borderColorChanged(m_borderColor);
#endif
}

void itemSettings::setBorderWidth(const int &width)
{
#if 0
    m_borderWidth = width;
    if(currentRectangle != nullptr){
        if(width == 0){
            currentRectangle->setPen(Qt::NoPen);
        } else {
            QPen pen(currentRectangle->pen().color(), width);
            currentRectangle->setPen(pen);
        }
    }
    emit borderWidthChanged(m_borderWidth);
#endif
}

void itemSettings::newRectangle(VERectangle *rect)
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

void itemSettings::loadRectangle(VERectangle *rect)
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

void itemSettings::deselect()
{
    currentRectangle = nullptr;
}

void itemSettings::setVisible(bool visible)
{
#if 0
    if(!visible && currentRectangle != nullptr){
        QWidget::setVisible(true);
    } else {
        QWidget::setVisible(visible);
    }
#endif
}

void itemSettings::comboBoxIndexChanged(int index)
{
#if 0
    switch (index) {
    case 1:
        ui->color_2->setVisible(true);
        ui->labelColor_2->setVisible(true);
        ui->labelColor_1->setText(trUtf8("color 1"));
        if(currentRectangle != nullptr){
            setGradient(currentRectangle);
        }
        break;
    default:
        ui->color_2->setVisible(false);
        ui->labelColor_2->setVisible(false);
        ui->labelColor_1->setText(trUtf8("background"));
        if(currentRectangle != nullptr){
            currentRectangle->setBrush(QBrush(m_color_1));
        }
        break;
    }
#endif
}

void itemSettings::setGradient(VERectangle *rectangle)
{
#if 0
    auto tmpRect = rectangle->rect();
    QLinearGradient gradient(tmpRect.left() + tmpRect.width()/2,
                             tmpRect.top(),
                             tmpRect.left() + tmpRect.width()/2,
                             tmpRect.bottom());
    gradient.setColorAt(0.0, m_color_1);
    gradient.setColorAt(1.0, m_color_2);
    rectangle->setBrush(QBrush(gradient));
#endif
}
