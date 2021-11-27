// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

#include "heightmapborderdrawer.h"

HeightMapBorderDrawer::HeightMapBorderDrawer()
{
}

QRectF HeightMapBorderDrawer::borderRect() const
{
    return m_borderRect;
}

void HeightMapBorderDrawer::setBorderRect(const QRectF &borderRect)
{
    m_borderRect = borderRect;
    update();
}

bool HeightMapBorderDrawer::updateData()
{
/*    m_lines = {
        {QVector3D(m_borderRect.x(), m_borderRect.y(), 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan)},
        {QVector3D(m_borderRect.x(), m_borderRect.y() + m_borderRect.height(), 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan)},
        {QVector3D(m_borderRect.x(), m_borderRect.y() + m_borderRect.height(), 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan)},
        {QVector3D(m_borderRect.x() + m_borderRect.width(), m_borderRect.y() + m_borderRect.height(), 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan)},
        {QVector3D(m_borderRect.x() + m_borderRect.width(), m_borderRect.y() + m_borderRect.height(), 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan)},
        {QVector3D(m_borderRect.x() + m_borderRect.width(), m_borderRect.y(), 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan)},
        {QVector3D(m_borderRect.x() + m_borderRect.width(), m_borderRect.y(), 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan)},
        {QVector3D(m_borderRect.x(), m_borderRect.y(), 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan)},
    };*/

    m_lines.clear();


    VertexData vd;
    vd.position = QVector3D(m_borderRect.x(), m_borderRect.y(), 0);
    vd.color = QVector3D(1.0, 0.0, 0.0);
    vd.start = QVector3D(sNan, sNan, sNan);
    m_lines.push_back(vd);

    vd.position = QVector3D(m_borderRect.x(), m_borderRect.y() + m_borderRect.height(), 0);
    m_lines.push_back(vd);
    m_lines.push_back(vd);


    vd.position = QVector3D(m_borderRect.x() + m_borderRect.width(), m_borderRect.y() + m_borderRect.height(), 0);
    m_lines.push_back(vd);
    m_lines.push_back(vd);


    vd.position = QVector3D(m_borderRect.x() + m_borderRect.width(), m_borderRect.y(), 0);
    m_lines.push_back(vd);
    m_lines.push_back(vd);


    vd.position = QVector3D(m_borderRect.x(), m_borderRect.y(), 0);
    m_lines.push_back(vd);


    return true;
}


