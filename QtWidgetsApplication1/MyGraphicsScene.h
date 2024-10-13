#pragma once
#include <qgraphicsscene.h>
class MyGraphicsScene :
    public QGraphicsScene
{
public:
    MyGraphicsScene(const QRectF& sceneRect, QObject* parent = nullptr) :QGraphicsScene(sceneRect, parent) {
    }
protected:

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
    virtual void wheelEvent(QGraphicsSceneWheelEvent* wheelEvent);

};

