#ifndef _ITEMSETTINGS_H_
#define _ITEMSETTINGS_H_

#include <QWidget>
#include "snail_types.h"

///class VERectangle;

namespace Ui {
class ItemSettings;
}

class item_Settings : public QWidget
{
    Q_OBJECT
 ///   Q_PROPERTY(QColor color_1 READ color_1 WRITE setColor_1 NOTIFY color_1Changed)
 ///   Q_PROPERTY(QColor color_2 READ color_2 WRITE setColor_2 NOTIFY color_2Changed)
 ///   Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)
  ///  Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth NOTIFY borderWidthChanged)

public:
    explicit item_Settings(QWidget *parent = 0);
    ~item_Settings();

    QColor BGcolor() const;
    QColor borderColor() const;
    quint8 borderThick() const;
    quint16 itemWidth() const;
    quint16 itemHeight() const;
    en_item_type itemType() const;
public slots:
    void setBGColor(const QColor &color);
    void setBorderColor(const QColor& color);
    void setBorderThick(const quint8 &thick);
    void setitemWidth(const quint16& width);
    void setitemHeight(const quint16& height);
    void setitemType(const en_item_type& height);

signals:
    void BGcolorChanged(const QColor &color);
    void borderColorChanged(const QColor &color);
    void borderThickChanged(const qint8 &thick);
    void itemWidthChanged(const quint16& width);
    void itemHeightChanged(const quint16& height);

private:
    Ui::ItemSettings*ui;
    en_item_type item_type;
  ///  VERectangle *currentItem;
  ///  QAbstractGraphicsShapeItem* currentItem;

public slots:
 ////   void newRectangle(VERectangle *rect);
 ///   void loadRectangle(VERectangle *rect);
    void deselect();
    void setVisible(bool visible) override;

private:
    QColor m_BGcolor;
    QColor m_borderColor;
    quint8 m_borderThick;
    quint16 m_width;
    quint16 m_height;
};

#endif // VERECTANGLESETTINGS_H
