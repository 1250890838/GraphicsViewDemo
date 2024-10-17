
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "MyGraphicsScene.h"
#include "PointItem.h"

MyGraphicsScene::MyGraphicsScene(const QRectF& sceneRect, QObject* parent)
	:QGraphicsScene(sceneRect, parent),
	m_state(None)
{
}

void MyGraphicsScene::onChangeSceneToGetRingLeftPressAndHoverPoint() {
	m_state = ForRingLeftPressAndHover;
}

void MyGraphicsScene::onChangeSceneToGetRingRightPressAndHoverPoint() {
	m_state = ForRingRightPressAndHover;
}

void MyGraphicsScene::onChangeSceneToGetCircleHoveredPoint() {
	m_state = ForCircleHover;
}

void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (m_state == ForCircleHover ||
		m_state == ForRingLeftPressAndHover ||
		m_state == ForRingRightPressAndHover ||
		m_state == ForPolygonLeftRightHover) {
		emit newHoveredPoint(mouseEvent->scenePos());
	}
	QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (mouseEvent->buttons() == Qt::LeftButton &&
		(m_state == ForCirclePress ||
			m_state == ForRingLeftPress ||
			m_state == ForRingLeftPressAndHover ||
			m_state == ForPolygonLeftRightHover)) {
		emit newLeftPressedPoint(mouseEvent->scenePos());
	}
	else if (mouseEvent->buttons() == Qt::RightButton &&
		(m_state == ForCircleHover ||
			m_state == ForRingRightPressAndHover ||
			m_state == ForPolygonLeftRightHover))
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
