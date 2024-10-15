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
        Rotate,
        Paint // just for painting,not other function
    };

    enum Pos {
        Outer,
        Inner
    };
public:
    PointItem(QGraphicsItem* parent, Edge edge,Pos pos=Inner);
    void setEdge(Edge edge) { m_edge = edge; }
    void adjustPosition();

protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;
private:
    void moveLogic(QPointF lastPos,QPointF pos);
private:
    QRectF m_rect;
    Edge m_edge;
    Pos m_pos;
};
