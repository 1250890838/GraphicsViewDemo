#pragma once
#include <QGraphicsitem.h>
#include <QList>

#include "PointItem.h"
#include "MyGraphicsScene.h"

class MyGraphicsItem :
	public QObject, public QAbstractGraphicsShapeItem
{
	Q_OBJECT
public:
	MyGraphicsItem(QGraphicsItem* parent = nullptr);
	MyGraphicsItem(QGraphicsItem* parent, qreal width, qreal height);

	void setRect(QRectF rect) { m_rect = rect; }
	QRectF rect() const { return m_rect; }

	QRectF lastRect() const { return m_lastRect; }
	void updateLastRect() { m_lastRect = m_rect; }

	virtual void setPen(const QPen& pen) { m_paintPen = pen; }
	QPen pen() { return m_paintPen; }
	// we need to adjust the point item position when their parent graphics item sized,moved or rotated.
	virtual void updatePointList();
	virtual QRectF boundingRect() const override;

	void appendPoint(PointItem* item);
	PointItem* pointAt(int i) const;
	int pointsCount() const;
	void clear();
public slots:
	virtual void onNewLeftPressedPoint(QPointF point) {}
	virtual void onNewRightPressedPoint(QPointF point) {
		disconnect(dynamic_cast<MyGraphicsScene*>(scene()), &MyGraphicsScene::newLeftPressedPoint, this, &MyGraphicsItem::onNewLeftPressedPoint);
		disconnect(dynamic_cast<MyGraphicsScene*>(scene()), &MyGraphicsScene::newHoveredPoint, this, &MyGraphicsItem::onNewHoveredPoint);
		disconnect(dynamic_cast<MyGraphicsScene*>(scene()), &MyGraphicsScene::newRightPressedPoint, this, &MyGraphicsItem::onNewRightPressedPoint);
	}
	virtual void onNewHoveredPoint(QPointF point) {}
protected:
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;

protected:
	QRectF m_rect;
	QRectF m_lastRect;
	QList<PointItem*> m_points;
private:
	QPen m_paintPen;
};
