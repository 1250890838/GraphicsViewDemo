
#include "MyRingGraphicsItem.h"
#include "MyGraphicsScene.h"

#include <QGraphicsScene>
#include <QPair>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <cmath>

RingGraphicsItem::RingGraphicsItem(QGraphicsItem* parent)
	:CircleGraphicsItem(parent),
	m_outerItem(new CircleGraphicsItem(this))
{
}

void RingGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	CircleGraphicsItem::mouseMoveEvent(event);
}

void RingGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	CircleGraphicsItem::mousePressEvent(event);
}

void RingGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	CircleGraphicsItem::mouseReleaseEvent(event);
}

void RingGraphicsItem::onNewLeftPressedPoint(QPointF point) {
	MyGraphicsScene* myScene = dynamic_cast<MyGraphicsScene*>(scene());
	if (m_points.count() < 2) {
		PointItem* item = new PointItem(nullptr, PointItem::Paint);
		item->setPos(point);
		myScene->addItem(item);
		m_points.append(item);
	}
	if (m_points.count() == 2)
		myScene->setState(MyGraphicsScene::ForLeftPress | MyGraphicsScene::ForHover);
	else if (m_points.count() == 3) {
		m_points[2]->setPos(point);
		pointsDetermineCircle();
		myScene->setState(MyGraphicsScene::ForRightPress | MyGraphicsScene::ForHover);
		PointItem* item = new PointItem(nullptr, PointItem::Paint);
		item->setPos(point);
		myScene->addItem(item);
		m_outerItem->appendPoint(item);
		m_outerItem->enablePainting = true;
	}
}

void RingGraphicsItem::onNewRightPressedPoint(QPointF point) {

	// the paint is finished,don't receive signal from scene and send signal to scene.
	MyGraphicsItem::onNewRightPressedPoint(point);

	QPointF hoverPoint = point;
	QPointF centerPoint = mapToScene(rect().center());
	qreal outerItemRadius = sqrt(pow(hoverPoint.x() - centerPoint.x(), 2) + pow(hoverPoint.y() - centerPoint.y(), 2));
	qreal innerItemRadius = rect().width() / 2;
	m_outerItem->setRect({ 0,0,outerItemRadius * 2,outerItemRadius * 2 });
	m_outerItem->setPos(QPointF{ innerItemRadius - outerItemRadius , innerItemRadius - outerItemRadius });

	clear();
	PointItem* innerLeftItem = new PointItem(this, PointItem::LeftSide);
	this->appendPoint(innerLeftItem);
	PointItem* innerTopItem = new PointItem(this, PointItem::TopSide);
	this->appendPoint(innerTopItem);
	PointItem* innerRightItem = new PointItem(this, PointItem::RightSide);
	this->appendPoint(innerRightItem);
	PointItem* innerBottomItem = new PointItem(this, PointItem::BottomSide);
	this->appendPoint(innerBottomItem);
	this->updatePointList();

	m_outerItem->clear();
	PointItem* outerLeftItem = new PointItem(m_outerItem, PointItem::LeftSide);
	m_outerItem->appendPoint(outerLeftItem);
	PointItem* outerTopItem = new PointItem(m_outerItem, PointItem::TopSide);
	m_outerItem->appendPoint(outerTopItem);
	PointItem* outerRightItem = new PointItem(m_outerItem, PointItem::RightSide);
	m_outerItem->appendPoint(outerRightItem);
	PointItem* outerBottomItem = new PointItem(m_outerItem, PointItem::BottomSide);
	m_outerItem->appendPoint(outerBottomItem);
	m_outerItem->pos() = pos();
	m_outerItem->updatePointList();
	setPos(pos());
}

void RingGraphicsItem::onNewHoveredPoint(QPointF point) {
	if (this->pointsCount() == 2) {
		PointItem* item = new PointItem(nullptr, PointItem::Paint);
		item->setPos(point);
		scene()->addItem(item);
		this->appendPoint(item);
		this->enablePainting = true;
		this->pointsDetermineCircle();
	}
	else if (this->pointsCount() == 3 && !m_outerItem->pointsCount()) {
		this->pointAt(2)->setPos(point);
		this->pointsDetermineCircle();
	}
	else if (m_outerItem->pointsCount()) {
		m_outerItem->pointAt(0)->setPos(point);
		QPointF hoverPoint = point;
		QPointF centerPoint = mapToScene(rect().center());
		qreal outerItemRadius = sqrt(pow(hoverPoint.x() - centerPoint.x(), 2) + pow(hoverPoint.y() - centerPoint.y(), 2));
		qreal innerItemRadius = rect().width() / 2;
		m_outerItem->setRect({ 0,0,outerItemRadius * 2,outerItemRadius * 2 });
		m_outerItem->setPos(QPointF{ innerItemRadius - outerItemRadius , innerItemRadius - outerItemRadius });
	}
}

void RingGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	CircleGraphicsItem::paint(painter, option, widget);
}

QPainterPath RingGraphicsItem::shape() const
{
	QPainterPath path, path2;
	path.addEllipse(this->rect());
	path2.addEllipse(m_outerItem->rect());
	path2 = mapFromItem(m_outerItem, path2);
	if (this->rect().width() == m_outerItem->rect().width()) {
		return path;
	}
	return rect().width() > m_outerItem->rect().width() ? path.subtracted(path2) : path2.subtracted(path);
}

QRectF RingGraphicsItem::boundingRect() const
{
	// rect returned from m_outerItem->rect() can't directly used,we need to convert it  to this coordinate System
	auto outerItemRect = m_outerItem->rect();
	outerItemRect.setX(outerItemRect.x() + m_outerItem->pos().x());
	outerItemRect.setY(outerItemRect.y() + m_outerItem->pos().y());
	return this->rect().width() > m_outerItem->rect().width() ? this->rect() : outerItemRect;
}
