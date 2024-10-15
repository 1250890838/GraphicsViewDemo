#pragma once
#include <QGraphicsitem.h>
#include <QList>
#include "PointItem.h"

class MyGraphicsItem :
    public QObject,public QAbstractGraphicsShapeItem
{
    Q_OBJECT
public:
    MyGraphicsItem(QGraphicsItem* parent = nullptr);
    MyGraphicsItem(QGraphicsItem* parent,qreal width,qreal height);
    
    void setRect(QRectF rect) { m_rect = rect; }
    QRectF rect() const { return m_rect; }
    
    virtual void updatePointList();
    virtual QRectF boundingRect() const override;
    
    void appendPoint(PointItem* item);
    PointItem* pointAt(int i);
    int pointsCount();
    void clear();
    
protected:
    QRectF m_rect;
    QList<PointItem*> m_points;
};

