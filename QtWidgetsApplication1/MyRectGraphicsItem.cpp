
#include "MyRectGraphicsItem.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "MyGraphicsScene.h"
#include "ImageProcessManager.h"

RectGraphicsItem::RectGraphicsItem(QGraphicsItem* parent, qreal width, qreal height)
	:MyGraphicsItem(parent, width, height)
{
	for (int i = 0; i < 9; i++) {
		PointItem* point = new PointItem(this, static_cast<PointItem::Edge>(i));
		m_points.append(point);
	}
	updatePointList();
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
	MyGraphicsItem::paint(painter, option, widget);
	painter->drawRect(m_rect);
}
