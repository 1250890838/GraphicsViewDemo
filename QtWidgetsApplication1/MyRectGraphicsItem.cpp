#include "MyRectGraphicsItem.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

RectGraphicsItem::RectGraphicsItem(QGraphicsItem* parent, qreal width, qreal height)
	:MyGraphicsItem(parent,width,height)
{
	for (int i = 0; i < 9; i++) {
		PointItem* point = new PointItem(this, static_cast<PointItem::Edge>(i));
		m_points.append(point);
	}
	updatePointList();

}

void RectGraphicsItem::updatePointList()
{
	/*
	QList<QPointF> positions = {
		{m_rect.x() + -4,m_rect.y() + -4},{m_rect.x() + -4,m_rect.y() + m_rect.height() / 2 - 4},{m_rect.x() + -4,m_rect.y() + m_rect.height() - 4},
		{m_rect.x() + m_rect.width() / 2 - 4,m_rect.y() + -4},{m_rect.x() + m_rect.width() / 2 - 4,m_rect.y() + m_rect.height() / 2 - 4},{m_rect.x() + m_rect.width() / 2 - 4,m_rect.y() + m_rect.height() - 4},
		{m_rect.x() + m_rect.width() - 4,m_rect.y() + -4},{m_rect.x() + m_rect.width() - 4,m_rect.y() + m_rect.height() / 2 - 4},{m_rect.x() + m_rect.width() - 4,m_rect.y() + m_rect.height() - 4}
	};
	*/
	for (auto item : m_points) {
		item->adjustPosition();
	}
}

void RectGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	MyGraphicsItem::mouseMoveEvent(event);
}

void RectGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	MyGraphicsItem::mousePressEvent(event);
}

void RectGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	MyGraphicsItem::mouseReleaseEvent(event);
}

void RectGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setPen(Qt::red);
	painter->drawRect(m_rect);
}