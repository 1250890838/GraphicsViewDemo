#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "MyGraphicsScene.h"
#include "PointItem.h"

MyGraphicsScene::MyGraphicsScene(const QRectF& sceneRect, QObject* parent)
	:QGraphicsScene(sceneRect, parent),
	m_state(None),
	m_pixmapItem(nullptr)
{
}

void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (m_state & ForHover) {
		emit newHoveredPoint(mouseEvent->scenePos());
	}
	QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (mouseEvent->buttons() == Qt::LeftButton &&
		(m_state & ForLeftPress)) {
		emit newLeftPressedPoint(mouseEvent->scenePos());
	}
	else if (mouseEvent->buttons() == Qt::RightButton &&
		(m_state & ForRightPress))
	{
		m_state = None;
		emit newRightPressedPoint(mouseEvent->scenePos());
	}
	QGraphicsScene::mousePressEvent(mouseEvent);
}

void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void MyGraphicsScene::wheelEvent(QGraphicsSceneWheelEvent* wheelEvent)
{
	QGraphicsScene::wheelEvent(wheelEvent);
}
