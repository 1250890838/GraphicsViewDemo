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
	auto rotatedPoint = m_points[9];
	rotatedPoint->setPos(m_rect.x() + m_rect.width() / 2 - 4, m_rect.y() - 15);
}
