#include "MyGraphicsView.h"

#include <QPixmap>
#include <QBrush>
#include <QWheelEvent>
#include <QDebug>

MyGraphicsView::MyGraphicsView(QGraphicsScene* scene) :QGraphicsView(scene) {
	setBackgroundBrush(QBrush(QColor(Qt::black)));
}

void MyGraphicsView::wheelEvent(QWheelEvent* event)
{
	static double scale = 0;
	if (event->angleDelta().y() > 0)
		scale += 0.01;
	else
		scale -= 0.01;
	if (scale >= 1 || scale <= -1)
		return;
	auto matrix = QTransform::fromScale(scale, 1 + scale);
	this->setTransform(QTransform::fromScale(1+scale, 1+scale),false);
	QGraphicsView::wheelEvent(event);
}

void MyGraphicsView::mousePressEvent(QMouseEvent* event)
{
	QGraphicsView::mousePressEvent(event);
}
