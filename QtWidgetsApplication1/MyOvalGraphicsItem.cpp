
#include "MyOvalGraphicsItem.h"

#include <QPainter>

OvalGraphicsItem::OvalGraphicsItem(QGraphicsItem* parent, qreal width, qreal height) :
	MyGraphicsItem(parent, width, height)
{
	m_points.append(new PointItem(this, PointItem::Left));
	m_points.append(new PointItem(this, PointItem::Top));
	m_points.append(new PointItem(this, PointItem::Right));
	m_points.append(new PointItem(this, PointItem::Bottom));
	m_points.append(new PointItem(this, PointItem::Rotate));
	updatePointList();
}

void OvalGraphicsItem::updatePointList()
{
	MyGraphicsItem::updatePointList();
	m_points[4]->setPos(m_points[1]->pos() + QPointF{ 0, -m_rect.height() * 0.15 }); // rotated point placed above top point
}

void OvalGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	MyGraphicsItem::mouseMoveEvent(event);
}

void OvalGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	MyGraphicsItem::mousePressEvent(event);
}

void OvalGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	MyGraphicsItem::mouseReleaseEvent(event);
}

void OvalGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	MyGraphicsItem::paint(painter, option, widget);
	painter->drawEllipse(m_rect);
}

QPainterPath OvalGraphicsItem::shape() const
{
	QPainterPath path;
	path.addEllipse(boundingRect());
	return path;
}
