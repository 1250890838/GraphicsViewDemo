#include "PointItem.h"
#include "MyGraphicsItem.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QDebug>

PointItem::PointItem(QGraphicsItem* parent, Edge edge,Pos pos)
    :QAbstractGraphicsShapeItem(parent),
    m_edge(edge),
    m_pos(pos),
    m_rect(QRectF(0, 0, 8, 8))
{
    this->setAcceptHoverEvents(true);
}

void PointItem::adjustPosition()
{
    if (parentItem() == nullptr)
        return;
    QRectF rect = dynamic_cast<MyGraphicsItem*>(parentItem())->rect();
    switch (m_edge)
    {
    case PointItem::LeftTop:
        setPos(rect.x() + -4, rect.y() + -4);
        break;
    case PointItem::Left:
        setPos(rect.x() + -4, rect.y() + rect.height() / 2 - 4);
        break;
    case PointItem::LeftBottom:
        setPos(rect.x() + -4, rect.y() + rect.height() - 4);
        break;
    case PointItem::Top:
        setPos(rect.x() + rect.width() / 2 - 4, rect.y()  -4);
        break;
    case PointItem::Middle:
        setPos(rect.x() + rect.width() / 2 - 4, rect.y() + rect.height() / 2 - 4);
        break;
    case PointItem::Bottom:
        setPos(rect.x() + rect.width() / 2 - 4, rect.y() + rect.height() - 4);
        break;
    case PointItem::RightTop:
        setPos(rect.x() + rect.width() - 4, rect.y() + -4);
        break;
    case PointItem::Right:
        setPos(rect.x() + rect.width() - 4, rect.y() + rect.height() / 2 - 4);
        break;
    case PointItem::RightBottom:
        setPos(rect.x() + rect.width() - 4, rect.y() + rect.height() - 4);
        break;
    case PointItem::Rotate:
        break;
    case PointItem::Paint:
        break;
    default:
        break;
    }
}

void PointItem::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    switch (m_edge)
    {
    case PointItem::LeftTop:
        setCursor(QCursor(Qt::SizeFDiagCursor));
        break;
    case PointItem::Left:
        setCursor(QCursor(Qt::SizeHorCursor));
        break;
    case PointItem::LeftBottom:
        setCursor(QCursor(Qt::SizeBDiagCursor));
        break;
    case PointItem::Top:
        setCursor(QCursor(Qt::SizeVerCursor));
        break;
    case PointItem::Middle:
        setCursor(QCursor(Qt::OpenHandCursor));
        break;
    case PointItem::Bottom:
        setCursor(QCursor(Qt::SizeVerCursor));
        break;
    case PointItem::RightTop:
        setCursor(QCursor(Qt::SizeBDiagCursor));
        break;
    case PointItem::Right:
        setCursor(QCursor(Qt::SizeHorCursor));
        break;
    case PointItem::RightBottom:
        setCursor(QCursor(Qt::SizeFDiagCursor));
        break;
    case PointItem::Rotate:
        setCursor(QCursor(Qt::WaitCursor));
        break;
    default:
        break;
    }
}

void PointItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    moveLogic(event->lastScenePos(),event->scenePos());
    QAbstractGraphicsShapeItem::mouseMoveEvent(event);
}

void PointItem::moveLogic(QPointF lastPos,QPointF pos)
{
    auto parentItem = dynamic_cast<MyGraphicsItem*>(this->parentItem());
    if (parentItem == nullptr || m_edge==Paint)
        return;

    QRectF rect = parentItem->rect();
    pos = parentItem->mapFromScene(pos);
    switch (m_edge)
    {
    case PointItem::LeftTop:
        rect.setTopLeft(pos);
        break;
    case PointItem::Left:   
        rect.setLeft(pos.x());
        break;
    case PointItem::LeftBottom:
        rect.setBottomLeft(pos);
        break;
    case PointItem::Top:
        rect.setTop(pos.y());
        break;
    case PointItem::Middle:
    {
        QPointF tempPos = parentItem->mapToScene(pos);
        parentItem->moveBy(tempPos.x() - lastPos.x(), tempPos.y() - lastPos.y());
    }
        break;
    case PointItem::Bottom:
        rect.setBottom(pos.y());
        break;
    case PointItem::RightTop:
        rect.setTopRight(pos);
        break;
    case PointItem::Right:
        rect.setRight(pos.x());
        break;
    case PointItem::RightBottom:
        rect.setBottomRight(pos);
        break;
    case PointItem::Rotate:
    {
        QPointF centerPos = parentItem->rect().center();
        qreal angle = atan2(pos.y()-centerPos.y(),  pos.x()- centerPos.x()) * 180 / M_PI;
        parentItem->setTransformOriginPoint(centerPos);
        parentItem->setRotation(parentItem->rotation() + angle + 90);
    }
        break;
    default:
        break;
    }
    parentItem->setRect(rect);
    parentItem->updatePointList();
    parentItem->update();
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
    if (parentItem() && parentItem()->isSelected()) {
        painter->setBrush(Qt::blue);
    }
    else {
        painter->setBrush(Qt::white);
    }
    painter->setPen(Qt::black);
    if (m_edge == Rotate) {
        painter->setBrush(Qt::yellow);
        painter->drawEllipse(m_rect);
    }
    else {
        painter->drawRect(m_rect);
    }
}
