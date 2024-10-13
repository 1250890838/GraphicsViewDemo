#pragma once
#include <qgraphicsitem.h>
class PointItem :
    public QAbstractGraphicsShapeItem
{
public:
    enum Edge {
        LeftTop,
        Left,
        LeftBottom,
        Top,
        Middle,
        Bottom,
        RightTop,
        Right,
        RightBottom,
        Rotate
    };
public:
    PointItem(QGraphicsItem* parent,Edge edge);
protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;
private:
    void moveLogic(qreal dx, qreal dy);
private:
    QRectF m_rect;
    Edge m_edge;
};

