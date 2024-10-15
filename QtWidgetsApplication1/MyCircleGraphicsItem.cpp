#include "MyCircleGraphicsItem.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QPair>

CircleGraphicsItem::CircleGraphicsItem(QGraphicsItem* parent):
	enablePainting(false)
{
}

void CircleGraphicsItem::onNewLeftPressedPoint(QPointF point) {
	PointItem* item = new PointItem(nullptr, PointItem::Paint);
	item->setPos(point);
	scene()->addItem(item);
	m_points.append(item);
	if (m_points.count() == 2)
		changeSceneToGetHoveredPoint();
}

void CircleGraphicsItem::onNewRightPressedPoint(QPointF point)
{
	m_points[2]->setPos(point);

	pointsDetermineCircle();
	for (auto item : m_points) {
		scene()->removeItem(item);
		delete item;
	}
	m_points.clear();

	PointItem* left = new PointItem(this, PointItem::Left);
	PointItem* top = new PointItem(this, PointItem::Top);
	PointItem* right = new PointItem(this, PointItem::Right);
	PointItem* bottom = new PointItem(this, PointItem::Bottom);
	m_points.append({ left,top,right,bottom });
	updatePointList();
}

void CircleGraphicsItem::onNewHoveredPoint(QPointF point)
{
	if (m_points.count() == 2) {
		m_points.append(new PointItem(nullptr, PointItem::Paint));
		m_points[2]->setPos(point);
		scene()->addItem(m_points[2]);
		enablePainting = true;
	}
	m_points[2]->setPos(point);
	pointsDetermineCircle();
}

void CircleGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	MyGraphicsItem::mouseMoveEvent(event);
}

void CircleGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	MyGraphicsItem::mousePressEvent(event);
}

void CircleGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	MyGraphicsItem::mouseReleaseEvent(event);
}

void CircleGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if (!enablePainting) return;
	painter->setPen(Qt::red);
	painter->drawEllipse(m_rect);
}

void CircleGraphicsItem::pointsDetermineCircle()
{
	qreal radius;
	QPointF center;
	QPointF pt1 = m_points[0]->pos();
	QPointF pt2 = m_points[1]->pos();
	QPointF pt3 = m_points[2]->pos();

	qreal x1 = pt1.x(), x2 = pt2.x(), x3 = pt3.x();
	qreal y1 = pt1.y(), y2 = pt2.y(), y3 = pt3.y();
	qreal a = x1 - x2;
	qreal b = y1 - y2;
	qreal c = x1 - x3;
	qreal d = y1 - y3;
	qreal e = ((x1 * x1 - x2 * x2) + (y1 * y1 - y2 * y2)) / 2.0;
	qreal f = ((x1 * x1 - x3 * x3) + (y1 * y1 - y3 * y3)) / 2.0;
	qreal det = b * c - a * d;
	if (fabs(det) < 1e-5)
	{
		radius = -1;
		center = { 0,0 };
		return;
	}
	qreal x0 = -(d * e - b * f) / det;
	qreal y0 = -(a * f - c * e) / det;
	radius = hypot(x1 - x0, y1 - y0);

	center = { x0,y0 };
	m_rect = { 0,0,radius*2,radius*2 };
	setPos(QPointF{ x0,y0 } - QPointF{ radius,radius });
}
