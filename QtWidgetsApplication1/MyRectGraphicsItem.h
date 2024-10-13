#pragma once
#include <QRect>

#include "MyGraphicsItem.h"
#include "PointItem.h"

class RectGraphicsItem :
    public MyGraphicsItem
{
public:
    RectGraphicsItem(QGraphicsItem* parent,qreal width, qreal height);
    virtual void updatePointList() override;
protected:

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;
};

