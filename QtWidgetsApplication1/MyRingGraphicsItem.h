#pragma once
#include "MyCircleGraphicsItem.h"
class RingGraphicsItem :
    public MyGraphicsItem
{
    Q_OBJECT
public:
    RingGraphicsItem(QGraphicsItem* parent, CircleGraphicsItem* innerItem, CircleGraphicsItem* outerItem);
    virtual void updatePointList() override;
public slots:
    void onNewLeftPressedPoint(QPointF point);
    void onNewRightPressedPoint(QPointF point);
    void onNewHoveredPoint(QPointF point);
protected:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;
private:
    CircleGraphicsItem* m_innerItem;
    CircleGraphicsItem* m_outerItem;
signals:
    void changeSceneToGetRingLeftPressAndHoverPoint();
    void changeSceneToGetRingRightPressAndHoverPoint();
};

