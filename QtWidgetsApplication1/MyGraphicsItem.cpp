#include "MyGraphicsItem.h"

#include <QGraphicsScene>

MyGraphicsItem::MyGraphicsItem(QGraphicsItem* parent)
	:QAbstractGraphicsShapeItem(parent)
{
	this->setFlags(QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsFocusable
		| QGraphicsItem::ItemIsSelectable);
}

MyGraphicsItem::MyGraphicsItem(QGraphicsItem* parent, qreal width, qreal height)
	:MyGraphicsItem(parent)
{
	m_rect = {
		0,
		0,
		width,
		height
	};
}

QRectF MyGraphicsItem::boundingRect() const
{
	return m_rect;
}

void MyGraphicsItem::appendPoint(PointItem* item)
{
	m_points.append(item);
}

PointItem* MyGraphicsItem::pointAt(int i)
{
	return m_points[i];
}

int MyGraphicsItem::pointsCount()
{
	return m_points.count();
}

void MyGraphicsItem::clear()
{
	for (auto item : m_points) {
		scene()->removeItem(item);
		delete item;
	}
	m_points.clear();
}
