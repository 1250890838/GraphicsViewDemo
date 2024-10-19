
#pragma once
#include <QRect>

#include "MyGraphicsItem.h"
#include "PointItem.h"

class RectGraphicsItem :
    public MyGraphicsItem
{
public:
    RectGraphicsItem(QGraphicsItem* parent, qreal width, qreal height);
protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;
};
