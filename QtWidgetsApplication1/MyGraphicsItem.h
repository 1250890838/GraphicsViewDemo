#pragma once
#include <QGraphicsitem.h>
#include <QList>
#include "PointItem.h"

class MyGraphicsItem :
    public QAbstractGraphicsShapeItem
{
public:
    MyGraphicsItem(QGraphicsItem* parent=nullptr);
    void setRect(QRectF rect) { m_rect = rect; }
    QRectF rect() { return m_rect; }
    virtual void updatePointList() = 0;
protected:
    QRectF m_rect;
    QList<PointItem*> m_points;
};


