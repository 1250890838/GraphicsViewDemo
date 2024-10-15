#include "MyRingGraphicsItem.h"

#include <QGraphicsScene>
#include <QPair>
#include <QPainter>
#include <cmath>

RingGraphicsItem::RingGraphicsItem(QGraphicsItem* parent)
	:CircleGraphicsItem(parent),
	m_outerItem(new CircleGraphicsItem(this))
{
}

void RingGraphicsItem::onNewLeftPressedPoint(QPointF point) {
	if (m_points.count() < 2) {
		PointItem* item = new PointItem(nullptr, PointItem::Paint);
		item->setPos(point);
		scene()->addItem(item);
		m_points.append(item);
	}
	if (m_points.count() == 2)
		emit changeSceneToGetRingLeftPressAndHoverPoint();
	else if (m_points.count() == 3) {
		m_points[2]->setPos(point);
		pointsDetermineCircle();
		emit changeSceneToGetRingRightPressAndHoverPoint();
		PointItem* item = new PointItem(nullptr, PointItem::Paint);
		item->setPos(point);
		scene()->addItem(item);
		m_outerItem->appendPoint(item);
		m_outerItem->enablePainting = true;
	}
}

void RingGraphicsItem::onNewRightPressedPoint(QPointF point) {
	QPointF innerItemPoint = pos();
	qreal innerItemRadius = rect().width() / 2;
	QPointF innerItemCenter = innerItemPoint - QPointF{ innerItemRadius, innerItemRadius };
	qreal outerItemRadius = sqrt(pow(point.x() - innerItemCenter.x(), 2) + pow(point.y() - innerItemCenter.x(), 2));
	m_outerItem->setRect({ -(outerItemRadius - innerItemRadius),-(outerItemRadius - innerItemRadius),
		outerItemRadius * 2,outerItemRadius * 2 });

	clear();
	PointItem* innerLeftItem = new PointItem(this, PointItem::Left);
	this->appendPoint(innerLeftItem);
	PointItem* innerTopItem = new PointItem(this, PointItem::Top);
	this->appendPoint(innerTopItem);
	PointItem* innerRightItem = new PointItem(this, PointItem::Right);
	this->appendPoint(innerRightItem);
	PointItem* innerBottomItem = new PointItem(this, PointItem::Bottom);
	this->appendPoint(innerBottomItem);
	this->updatePointList();

	m_outerItem->clear();
	PointItem* outerLeftItem = new PointItem(m_outerItem, PointItem::Left);
	m_outerItem->appendPoint(outerLeftItem);
	PointItem* outerTopItem = new PointItem(m_outerItem, PointItem::Top);
	m_outerItem->appendPoint(outerTopItem);
	PointItem* outerRightItem = new PointItem(m_outerItem, PointItem::Right);
	m_outerItem->appendPoint(outerRightItem);
	PointItem* outerBottomItem = new PointItem(m_outerItem, PointItem::Bottom);
	m_outerItem->appendPoint(outerBottomItem);
	m_outerItem->pos() = pos();
	m_outerItem->updatePointList();
	setPos(pos());
}

void RingGraphicsItem::onNewHoveredPoint(QPointF point) {
	if (this->pointsCount() == 2) {
		PointItem* item = new PointItem(nullptr,PointItem::Paint);
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
		QPointF innerItemPoint = this->pos();
		qreal innerItemRadius = this->rect().width() / 2;
		QPointF innerItemCenter = innerItemPoint - QPointF{ innerItemRadius, innerItemRadius };
		qreal outerItemRadius = sqrt(pow(point.x() - innerItemCenter.x(), 2) + pow(point.y() - innerItemCenter.x(), 2));
		m_outerItem->setRect({ -(outerItemRadius - innerItemRadius),-(outerItemRadius - innerItemRadius),
			outerItemRadius * 2,outerItemRadius * 2 });
		m_outerItem->setPos(this->mapFromScene(this->pos()));
	}
}

QRectF RingGraphicsItem::boundingRect() const {
	QRectF innerRect = rect();
	QRectF outerRect = m_outerItem->rect();
	return innerRect.width() > outerRect.width() ? innerRect : outerRect;
}

void RingGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	CircleGraphicsItem::paint(painter, option, widget);
}
