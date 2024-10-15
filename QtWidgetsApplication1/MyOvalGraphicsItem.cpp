#include "MyOvalGraphicsItem.h"

#include <QPainter>

OvalGraphicsItem::OvalGraphicsItem(QGraphicsItem* parent, qreal width, qreal height):
	MyGraphicsItem(parent,width,height)
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
	/*
		m_points[0]->setPos(QPointF{ m_rect.x() - 4,m_rect.y() + m_rect.height() / 2 - 4 });
		m_points[1]->setPos(QPointF{ m_rect.x() + m_rect.width() / 2 - 4,m_rect.y() - 4 });
		m_points[2]->setPos(QPointF{ m_rect.x() + m_rect.width() - 4,m_rect.y() + m_rect.height() / 2 - 4 });
		m_points[3]->setPos(QPointF{ m_rect.x() + m_rect.width() / 2 - 4,m_rect.y() + m_rect.height() - 4 });
	*/
	for (auto item : m_points) {
		item->adjustPosition();
	}
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
	painter->setPen(Qt::red);
	painter->drawEllipse(m_rect);
}
