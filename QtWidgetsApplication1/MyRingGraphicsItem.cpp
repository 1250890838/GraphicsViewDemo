#include "MyRingGraphicsItem.h"

#include <QGraphicsScene>
#include <QPair>
#include <QPainter>
#include <cmath>

RingGraphicsItem::RingGraphicsItem(QGraphicsItem* parent,CircleGraphicsItem* innerItem,CircleGraphicsItem* outerItem)
	:MyGraphicsItem(parent),
	m_innerItem(innerItem),
	m_outerItem(outerItem)
{
}

void RingGraphicsItem::updatePointList()
{
}

void RingGraphicsItem::onNewLeftPressedPoint(QPointF point) {
	if (m_innerItem->pointsCount() < 2) {
		PointItem* item = new PointItem(nullptr, PointItem::Paint);
		item->setPos(point);
		scene()->addItem(item);
		m_innerItem->appendPoint(item);
	}
	if (m_innerItem->pointsCount() == 2)
		emit changeSceneToGetRingLeftPressAndHoverPoint();
	else if (m_innerItem->pointsCount() == 3) {
		m_innerItem->pointAt(2)->setPos(point);
		m_innerItem->pointsDetermineCircle();
		emit changeSceneToGetRingRightPressAndHoverPoint();
		PointItem* item = new PointItem(nullptr, PointItem::Paint);
		item->setPos(point);
		scene()->addItem(item);
		m_outerItem->appendPoint(item);
		m_outerItem->enablePainting = true;
	}
}

void RingGraphicsItem::onNewRightPressedPoint(QPointF point) {
	QPointF innerItemPoint = m_innerItem->pos();
	qreal innerItemRadius = m_innerItem->rect().width() / 2;
	QPointF innerItemCenter = innerItemPoint - QPointF{ innerItemRadius, innerItemRadius };
	qreal outerItemRadius = sqrt(pow(point.x() - innerItemCenter.x(), 2) + pow(point.y() - innerItemCenter.x(), 2));
	m_outerItem->setRect({ -(outerItemRadius - innerItemRadius),-(outerItemRadius - innerItemRadius),
		outerItemRadius * 2,outerItemRadius * 2 });

	m_innerItem->clear();
	PointItem* innerLeftItem = new PointItem(m_innerItem, PointItem::Left);
	m_innerItem->appendPoint(innerLeftItem);
	PointItem* innerTopItem = new PointItem(m_innerItem, PointItem::Top);
	m_innerItem->appendPoint(innerTopItem);
	PointItem* innerRightItem = new PointItem(m_innerItem, PointItem::Right);
	m_innerItem->appendPoint(innerRightItem);
	PointItem* innerBottomItem = new PointItem(m_innerItem, PointItem::Bottom);
	m_innerItem->appendPoint(innerBottomItem);
	m_innerItem->updatePointList();

	m_outerItem->clear();
	PointItem* outerLeftItem = new PointItem(m_outerItem, PointItem::Left);
	m_outerItem->appendPoint(outerLeftItem);
	PointItem* outerTopItem = new PointItem(m_outerItem, PointItem::Top);
	m_outerItem->appendPoint(outerTopItem);
	PointItem* outerRightItem = new PointItem(m_outerItem, PointItem::Right);
	m_outerItem->appendPoint(outerRightItem);
	PointItem* outerBottomItem = new PointItem(m_outerItem, PointItem::Bottom);
	m_outerItem->appendPoint(outerBottomItem);
	m_outerItem->pos() = m_innerItem->pos();
	m_outerItem->updatePointList();
	setPos(m_innerItem->pos());
}

void RingGraphicsItem::onNewHoveredPoint(QPointF point) {
	if (m_innerItem->pointsCount() == 2) {
		PointItem* item = new PointItem(nullptr,PointItem::Paint);
		item->setPos(point);
		scene()->addItem(item);
		m_innerItem->appendPoint(item);
		m_innerItem->enablePainting = true;
		m_innerItem->pointsDetermineCircle();
	}
	else if (m_innerItem->pointsCount() == 3 && !m_outerItem->pointsCount()) {
		m_innerItem->pointAt(2)->setPos(point);
		m_innerItem->pointsDetermineCircle();
	}
	else if (m_outerItem->pointsCount()) {
		m_outerItem->pointAt(0)->setPos(point);
		QPointF innerItemPoint = m_innerItem->pos();
		qreal innerItemRadius = m_innerItem->rect().width() / 2;
		QPointF innerItemCenter = innerItemPoint - QPointF{ innerItemRadius, innerItemRadius };
		qreal outerItemRadius = sqrt(pow(point.x() - innerItemCenter.x(), 2) + pow(point.y() - innerItemCenter.x(), 2));
		m_outerItem->setRect({ -(outerItemRadius - innerItemRadius),-(outerItemRadius - innerItemRadius),
			outerItemRadius * 2,outerItemRadius * 2 });
		m_outerItem->setPos(m_innerItem->pos());
	}
}

QRectF RingGraphicsItem::boundingRect() const {
	QRectF innerRect = m_innerItem->rect();
	QRectF outerRect = m_outerItem->rect();
	return innerRect.width() > outerRect.width() ? innerRect : outerRect;
}

void RingGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->save();

	painter->restore();
}
