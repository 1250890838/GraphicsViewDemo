
#pragma once
#include "MyGraphicsItem.h"
class CircleGraphicsItem :
    public MyGraphicsItem
{
    Q_OBJECT
public:
    CircleGraphicsItem(QGraphicsItem* parent);
    void pointsDetermineCircle();
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
public:
    bool enablePainting;
};
