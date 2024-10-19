#include "MyPolygonGraphicsItem.h"

#include <MyGraphicsScene.h>
#include <QPainter>

PolygonGraphicsItem::PolygonGraphicsItem(QGraphicsItem* parent) :
	MyGraphicsItem(parent),
	endToEnd(false),
	m_hoveredItem(new PointItem(nullptr, PointItem::Paint))
{
	m_hoveredItem->setVisible(false);
}

void PolygonGraphicsItem::onNewLeftPressedPoint(QPointF point)
{
	PointItem* item = new PointItem(nullptr, PointItem::Paint);
	item->setPos(point);
	scene()->addItem(item);
	appendPoint(item);

	m_hoveredItem->setPos(point);
	m_hoveredItem->setVisible(true);
}

void PolygonGraphicsItem::onNewRightPressedPoint(QPointF point)
{
	disconnect(dynamic_cast<MyGraphicsScene*>(scene()), &MyGraphicsScene::newLeftPressedPoint, this, &PolygonGraphicsItem::onNewLeftPressedPoint);
	disconnect(dynamic_cast<MyGraphicsScene*>(scene()), &MyGraphicsScene::newHoveredPoint, this, &PolygonGraphicsItem::onNewHoveredPoint);
	disconnect(dynamic_cast<MyGraphicsScene*>(scene()), &MyGraphicsScene::newRightPressedPoint, this, &PolygonGraphicsItem::onNewRightPressedPoint);

	scene()->removeItem(m_hoveredItem);
	delete m_hoveredItem;
	m_hoveredItem = nullptr;
	endToEnd = true;
	update();

	adjustPosAndSize();
	for (auto point : m_points) {
		point->setEdge(PointItem::Polygon);
		point->setParentItem(this);
		point->setPos(mapFromScene(point->pos()));
	}
}

void PolygonGraphicsItem::onNewHoveredPoint(QPointF point)
{
	m_hoveredItem->setPos(point);
	update();
}

void PolygonGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	MyGraphicsItem::mouseMoveEvent(event);
}

void PolygonGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	MyGraphicsItem::mousePressEvent(event);
}

void PolygonGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	MyGraphicsItem::mouseReleaseEvent(event);
}

void PolygonGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	MyGraphicsItem::paint(painter, option, widget);
	QPolygonF polygon;
	for (auto point : m_points) {
		polygon.append(point->pos()-QPointF{-4,-4});
	}
	if (!endToEnd) {
		polygon.append((m_hoveredItem->pos() - QPointF{ -4,-4 }));
		painter->drawPolyline(polygon);
	}
	else {
		painter->drawPolygon(polygon);
	}
}

QPainterPath PolygonGraphicsItem::shape() const
{
	QPainterPath path;
	QPolygonF polygon;
	for (auto point : m_points) {
		polygon.append(point->pos() - QPointF{ -4,-4 });
	}
	path.addPolygon(polygon);
	return path;
}

void PolygonGraphicsItem::adjustPosAndSize()
{
	QPolygonF polygon;
	for (auto point : m_points) {
		polygon.append(point->pos() - QPointF{ -4,-4 });
	}
	QRectF temp = polygon.boundingRect();
	m_rect = { 0,0,temp.width(),temp.height() };

	qreal minx = m_points[0]->x(), miny = m_points[0]->y();
	for (auto point : m_points) {
		minx = fmin(point->x(), minx);
		miny = fmin(point->y(), miny);
	}
	setPos(minx, miny);
}