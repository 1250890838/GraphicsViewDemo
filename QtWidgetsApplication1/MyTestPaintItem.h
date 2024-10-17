#pragma once
#include "MyGraphicsItem.h"
class MyTestPaintItem :
    public MyGraphicsItem
{
public:
    MyTestPaintItem(QGraphicsItem* parent, qreal width, qreal height);
protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;
};

