#include "MyGraphicsItem.h"

MyGraphicsItem::MyGraphicsItem(QGraphicsItem* parent)
	:QAbstractGraphicsShapeItem(parent)
{
	this->setFlags(QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsFocusable
		| QGraphicsItem::ItemIsSelectable);
}

