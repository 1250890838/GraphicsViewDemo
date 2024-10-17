
#pragma once
#include "MyCircleGraphicsItem.h"
class RingGraphicsItem :
    public CircleGraphicsItem
{
    Q_OBJECT
public:
    RingGraphicsItem(QGraphicsItem* parent);
public slots:
    void onNewLeftPressedPoint(QPointF point);
    void onNewRightPressedPoint(QPointF point);
    void onNewHoveredPoint(QPointF point);
protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;
    virtual QPainterPath shape() const override;
private:
    CircleGraphicsItem* m_outerItem;
signals:
    void changeSceneToGetRingLeftPressAndHoverPoint();
    void changeSceneToGetRingRightPressAndHoverPoint();
};
