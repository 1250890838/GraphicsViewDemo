#include "MainWindow.h"

#include <QCombobox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsItem> 
#include <QFileDialog>
#include <QPixmap>

#include "MyGraphicsScene.h"
#include "MyGraphicsView.h"
#include "MyRectGraphicsItem.h"
#include "MyRotatedRectGraphicsItem.h"
#include "MyOvalGraphicsItem.h"
#include "MyCircleGraphicsItem.h"
#include "MyRingGraphicsItem.h"

MainWindow::MainWindow() :
	m_scene(new MyGraphicsScene(QRectF(QPointF(0, 0), QPointF(600, 600)), this)),
	m_view(new MyGraphicsView(m_scene)),
	m_currItem(nullptr) {

	m_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	m_combobox = new QComboBox;
	m_combobox->addItem("Rectangle");
	m_combobox->addItem("Rotated Rectangle");
	m_combobox->addItem("Circle");
	m_combobox->addItem("Oval");
	m_combobox->addItem("Ring");
	m_combobox->addItem("Arc");
	m_combobox->addItem("Polygon");

	QHBoxLayout* hLayout = new QHBoxLayout;

	m_addImageButton = new QPushButton("add Image");
	connect(m_addImageButton, &QPushButton::clicked, this, &MainWindow::onAddImage);
	m_clearButton = new QPushButton("clear");
	connect(m_clearButton, &QPushButton::clicked, m_scene, &QGraphicsScene::clear);

	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->addWidget(m_addImageButton);
	vLayout->addWidget(m_combobox);
	vLayout->addWidget(m_clearButton);

	hLayout->addLayout(vLayout);
	hLayout->addWidget(m_view);

	QWidget* widget = new QWidget;
	widget->setLayout(hLayout);
	this->setCentralWidget(widget);

	connect(m_combobox, QOverload<int>::of(&QComboBox::currentIndexChanged),
		this, &MainWindow::onShapeSelectionChanged);
}

void MainWindow::onAddImage() {
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
	m_scene->clear();
	auto item = m_scene->addPixmap(QPixmap(fileName));
	item->setFlags(QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsFocusable
		| QGraphicsItem::ItemIsSelectable);
}

void MainWindow::onShapeSelectionChanged(int index) {
	MyGraphicsItem* item = nullptr;
	switch (index)
	{
	case 0:
		item = new RectGraphicsItem(nullptr, 200, 120);
		m_scene->setState(MyGraphicsScene::None);
		break;
	case 1:
		item = new RotatedRectGraphicsItem(nullptr, 200, 120);
		m_scene->setState(MyGraphicsScene::None);
		break;
	case 2:
		item = new CircleGraphicsItem(nullptr);
		m_scene->setState(MyGraphicsScene::ForCirclePress);
		connect(dynamic_cast<CircleGraphicsItem*>(item), &CircleGraphicsItem::changeSceneToGetHoveredPoint, m_scene, &MyGraphicsScene::onChangeSceneToGetCircleHoveredPoint);
		connect(m_scene, &MyGraphicsScene::newLeftPressedPoint, dynamic_cast<CircleGraphicsItem*>(item), &CircleGraphicsItem::onNewLeftPressedPoint);
		connect(m_scene, &MyGraphicsScene::newHoveredPoint, dynamic_cast<CircleGraphicsItem*>(item), &CircleGraphicsItem::onNewHoveredPoint);
		connect(m_scene, &MyGraphicsScene::newRightPressedPoint, dynamic_cast<CircleGraphicsItem*>(item), &CircleGraphicsItem::onNewRightPressedPoint);
		break;
	case 3:
		item = new OvalGraphicsItem(nullptr, 200, 120);
		m_scene->setState(MyGraphicsScene::None);
		break;
	case 4:
	{
		CircleGraphicsItem* innerItem = new CircleGraphicsItem(nullptr);
		CircleGraphicsItem* outerItem = new CircleGraphicsItem(nullptr);
		item = new RingGraphicsItem(nullptr, innerItem, outerItem);
		m_scene->addItem(innerItem);
		m_scene->addItem(outerItem);
		m_scene->setState(MyGraphicsScene::ForCirclePress);
		connect(dynamic_cast<RingGraphicsItem*>(item), &RingGraphicsItem::changeSceneToGetRingLeftPressAndHoverPoint, m_scene, &MyGraphicsScene::onChangeSceneToGetRingLeftPressAndHoverPoint);
		connect(dynamic_cast<RingGraphicsItem*>(item), &RingGraphicsItem::changeSceneToGetRingRightPressAndHoverPoint, m_scene, &MyGraphicsScene::onChangeSceneToGetRingRightPressAndHoverPoint);
		connect(m_scene, &MyGraphicsScene::newLeftPressedPoint, dynamic_cast<RingGraphicsItem*>(item), &RingGraphicsItem::onNewLeftPressedPoint);
		connect(m_scene, &MyGraphicsScene::newHoveredPoint, dynamic_cast<RingGraphicsItem*>(item), &RingGraphicsItem::onNewHoveredPoint);
		connect(m_scene, &MyGraphicsScene::newRightPressedPoint, dynamic_cast<RingGraphicsItem*>(item), &RingGraphicsItem::onNewRightPressedPoint);
	}
		break;
	case 5:
		break;
	case 6:
		break;
	default:
		break;
	}
	if (item) {
		m_scene->addItem(item);
	}
}