
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
        ForCirclePress,
        ForCircleHover,
        ForRingLeftPress,
        ForRingLeftPressAndHover,
        ForRingRightPressAndHover,
        ForPolygonLeftRightHover
    };
public:
    MyGraphicsScene(const QRectF& sceneRect, QObject* parent = nullptr);
    void setState(State state) { m_state = state; }
    QGraphicsItem* pixmapItem() { return m_pixmapItem; }
    void setPixmapItem(QGraphicsItem* item) { m_pixmapItem = item; }
public slots:
    void onChangeSceneToGetCircleHoveredPoint();
    void onChangeSceneToGetRingLeftPressAndHoverPoint();
    void onChangeSceneToGetRingRightPressAndHoverPoint();
signals:
    void newLeftPressedPoint(QPointF point);
    void newHoveredPoint(QPointF point);
    void newRightPressedPoint(QPointF point);

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
    virtual void wheelEvent(QGraphicsSceneWheelEvent* wheelEvent);
private:
    State m_state;
    QGraphicsItem* m_pixmapItem;
};