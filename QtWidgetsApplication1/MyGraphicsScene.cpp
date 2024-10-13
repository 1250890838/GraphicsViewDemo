#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "MyGraphicsScene.h"

void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
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
