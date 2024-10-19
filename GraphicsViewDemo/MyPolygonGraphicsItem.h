#pragma once
#include "MyGraphicsItem.h"
class PolygonGraphicsItem :
    public MyGraphicsItem
{
public:
    PolygonGraphicsItem(QGraphicsItem*);
public slots:
    void onNewLeftPressedPoint(QPointF point);
    void onNewRightPressedPoint(QPointF point);
    void onNewHoveredPoint(QPointF point);
protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;
    QPainterPath shape() const override;
private:
    void adjustPosAndSize();
private:
    PointItem* m_hoveredItem;
    bool endToEnd;
};
