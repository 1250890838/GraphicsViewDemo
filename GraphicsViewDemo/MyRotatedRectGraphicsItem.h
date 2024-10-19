#pragma once
#include "MyRectGraphicsItem.h"
class RotatedRectGraphicsItem :
    public RectGraphicsItem
{
public:
    RotatedRectGraphicsItem(QGraphicsItem* parent, qreal width, qreal height);
    virtual void updatePointList() override;
};