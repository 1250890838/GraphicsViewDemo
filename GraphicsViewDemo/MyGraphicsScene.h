#pragma once
#include <qgraphicsscene.h>
#include <QMouseEvent> 
#include <QObject>

#include "PointItem.h"

class MyGraphicsScene :
    public QGraphicsScene
{
    Q_OBJECT

public:
    enum State {
        None,
        ForLeftPress = 0x1,
        ForHover = 0x2,
        ForRightPress = 0x4
    };
public:
    MyGraphicsScene(const QRectF& sceneRect, QObject* parent = nullptr);
    void setState(int state) { m_state = state; }
    QGraphicsItem* pixmapItem() { return m_pixmapItem; }
    void setPixmapItem(QGraphicsItem* item) { m_pixmapItem = item; }
    void clearExceptPixmapItem();
protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
    virtual void wheelEvent(QGraphicsSceneWheelEvent* wheelEvent);
signals:
    void newLeftPressedPoint(QPointF point);
    void newHoveredPoint(QPointF point);
    void newRightPressedPoint(QPointF point);
private:
    int m_state;
    QGraphicsItem* m_pixmapItem;
};
