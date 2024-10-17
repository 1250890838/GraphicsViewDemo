#include "MyRotatedRectGraphicsItem.h"

RotatedRectGraphicsItem::RotatedRectGraphicsItem(QGraphicsItem* parent, qreal width, qreal height)
	:RectGraphicsItem(parent, width, height) {
	auto rotatedPoint = new PointItem(this, PointItem::Rotate);
	rotatedPoint->setParentItem(this);
	m_points.append(rotatedPoint);
	updatePointList();
}

void RotatedRectGraphicsItem::updatePointList()
{
	RectGraphicsItem::updatePointList();
	auto rotatedPoint = m_points[static_cast<int>(PointItem::Rotate)];
	rotatedPoint->setPos(rect().x() + rect().width() / 2 - 4, rect().y() - 0.15 * rect().height());
}