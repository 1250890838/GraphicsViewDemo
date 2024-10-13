#include "PointItem.h"
#include "MyGraphicsItem.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

PointItem::PointItem(QGraphicsItem* parent,Edge edge)
    :QAbstractGraphicsShapeItem(parent),
    m_edge(edge),
    m_rect(QRectF(0, 0, 8, 8))
{
    this->setAcceptHoverEvents(true);
}

void PointItem::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    switch (m_edge)
    {
    case PointItem::LeftTop:
        break;
    case PointItem::Left:
        setCursor(QCursor(Qt::SizeVerCursor));
        break;
    case PointItem::LeftBottom:
        break;
    case PointItem::Top:
        setCursor(QCursor(Qt::SizeHorCursor));
        break;
    case PointItem::Middle:
        break;
    case PointItem::Bottom:
        setCursor(QCursor(Qt::SizeHorCursor));
        break;
    case PointItem::RightTop:
        break;
    case PointItem::Right:
        setCursor(QCursor(Qt::SizeVerCursor));
        break;
    case PointItem::RightBottom:
        break;
    default:
        break;
    }
}

void PointItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF currPos = event->scenePos();
    QPointF lastPos = event->lastScenePos();
    qreal dx = currPos.x() - lastPos.x();
    qreal dy = currPos.y() - lastPos.y();
    moveLogic(dx, dy);
    QAbstractGraphicsShapeItem::mouseMoveEvent(event);
}

void PointItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
}

void PointItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QAbstractGraphicsShapeItem::mouseReleaseEvent(event);
}

QRectF PointItem::boundingRect() const
{
	return m_rect;
}

void PointItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setBrush(Qt::blue);
    painter->setPen(Qt::black);
    painter->drawRect(m_rect);
}

void PointItem::moveLogic(qreal dx, qreal dy)
{
    auto parentItem = dynamic_cast<MyGraphicsItem*>(this->parentItem());
    auto rect=parentItem->rect();
    switch (m_edge)
    {
    case PointItem::LeftTop:
        rect.setTopLeft(rect.topLeft() + QPointF{ dx,dy });
        break;
    case PointItem::Left:
        rect.setLeft(rect.left() + dx);
        break;
    case PointItem::LeftBottom:
        rect.setBottomLeft(rect.bottomLeft() + QPointF{ dx, dy });
        break;
    case PointItem::Top:
        rect.setTop(rect.top() + dy);
        break;
    case PointItem::Middle:
        break;
    case PointItem::Bottom:
        rect.setBottom(rect.bottom() + dy);
        break;
    case PointItem::RightTop:
        rect.setTopRight(rect.bottomRight() + QPointF{ dx,dy });
        break;
    case PointItem::Right:
        rect.setRight(rect.right() + dx);
        break;
    case PointItem::RightBottom:
        rect.setBottomRight(rect.bottomRight() + QPointF{ dx,dy });
        break;
    default:
        break;
    }
    parentItem->setRect(rect);
    parentItem->updatePointList();
    parentItem->update();
}
