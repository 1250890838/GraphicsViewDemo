#pragma once
#include <qgraphicsview.h>
class MyGraphicsView :
    public QGraphicsView
{
public:
    MyGraphicsView(QGraphicsScene* scene);
protected:
    virtual void wheelEvent(QWheelEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
private:
};

