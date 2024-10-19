
#pragma once
#include <QGraphicsitem.h>
#include <QList>
#include "PointItem.h"

class MyGraphicsItem :
    public QObject, public QAbstractGraphicsShapeItem
{
    Q_OBJECT
public:
    MyGraphicsItem(QGraphicsItem* parent = nullptr);
    MyGraphicsItem(QGraphicsItem* parent, qreal width, qreal height);

    void setRect(QRectF rect) { m_rect = rect; }
    QRectF rect() const { return m_rect; }

    QRectF lastRect() { return m_lastRect; }
    void updateLastRect() { m_lastRect = m_rect; }

    virtual void updatePointList();
    virtual QRectF boundingRect() const override;

    void appendPoint(PointItem* item);
    PointItem* pointAt(int i);
    int pointsCount();
    void clear();
protected:
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;

protected:
    QRectF m_rect;
    QRectF m_lastRect;
    QList<PointItem*> m_points;
};
