#include "MyGraphicsItem.h"

#include <QGraphicsScene>
#include <QPainter>

#include "MyGraphicsScene.h"
#include "ImageProcessManager.h"

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
	m_lastRect = m_rect;
}

QRectF MyGraphicsItem::boundingRect() const
{
	return rect();
}

void MyGraphicsItem::appendPoint(PointItem* item)
{
	m_points.append(item);
}

PointItem* MyGraphicsItem::pointAt(int i) const
{
	return m_points[i];
}

int MyGraphicsItem::pointsCount() const
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

void MyGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	auto pixmapItem = dynamic_cast<MyGraphicsScene*>(scene())->pixmapItem();
	if (!pixmapItem) {
		QGraphicsItem::mouseReleaseEvent(event);
		return;
	}

	QPainterPath paths = this->shape();
	QTransform trans = transform();
	trans.translate(lastRect().center().x(), lastRect().center().y());
	trans.rotate(rotation());
	trans.translate(-lastRect().center().x(), -lastRect().center().y());
	paths = trans.map(paths);

	QPainterPath pixmapPaths = pixmapItem->shape();
	paths.translate(pixmapItem->mapFromScene(this->pos()));
	QPainterPath intersectedPaths = paths.intersected(pixmapPaths);
	ImageProcessManager::getInstance().processArea(intersectedPaths);
	QGraphicsItem::mouseReleaseEvent(event);
}

void MyGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QPen pen(Qt::red);
	pen.setWidth(4);
	painter->setPen(pen);
}

void MyGraphicsItem::updatePointList()
{
	for (auto item : m_points) {
		item->adjustPosition();
	}
}
