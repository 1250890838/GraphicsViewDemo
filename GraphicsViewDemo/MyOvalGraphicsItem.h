
#pragma once
#include "MyGraphicsItem.h"

class OvalGraphicsItem :
    public MyGraphicsItem
{
public:
    OvalGraphicsItem(QGraphicsItem* parent, qreal width, qreal height);
    virtual void updatePointList() override;
protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;
    virtual QPainterPath shape() const override;
};
