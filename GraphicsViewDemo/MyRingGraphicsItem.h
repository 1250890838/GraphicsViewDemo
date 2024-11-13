#pragma once
#include "MyCircleGraphicsItem.h"

class RingGraphicsItem :
    public CircleGraphicsItem
{
    Q_OBJECT
public:
    RingGraphicsItem(QGraphicsItem* parent);
    virtual void setPen(const QPen& pen) override;

public slots:
    virtual void onNewLeftPressedPoint(QPointF point) override;
    virtual void onNewRightPressedPoint(QPointF point) override;
    virtual void onNewHoveredPoint(QPointF point) override;
protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;
    virtual QPainterPath shape() const override;
    virtual QRectF boundingRect() const override;

private:
    CircleGraphicsItem* m_outerItem;
};
