#include "MyTestPaintItem.h"

#include <QPainter>

MyTestPaintItem::MyTestPaintItem(QGraphicsItem* parent,qreal width,qreal height)
	:MyGraphicsItem(parent,width,height){
}

void MyTestPaintItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QPainterPath paths1;
	paths1.addRect(0, 0, 200, 200);
	QPainterPath paths2;
	paths2.addEllipse(100, 100, 200, 200);
	QPainterPath result=paths1.intersected(paths2);
	painter->setPen(Qt::red);
	painter->drawPath(paths1);
	painter->drawPath(paths2);
	auto count = result.elementCount();
	painter->fillPath(result,QBrush(Qt::blue));
	for (int i = 0; i < count; i++) {
		auto element = result.elementAt(i);
		int n = 3;
	}
}
