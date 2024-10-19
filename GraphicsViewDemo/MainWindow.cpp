#include "MainWindow.h"

#include <QCombobox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsItem> 
#include <QFileDialog>
#include <QPixmap>
#include <QSplitter>
#include <QSlider>
#include <QGridLayout>
#include <QApplication>

#include "MyGraphicsScene.h"
#include "MyGraphicsView.h"
#include "MyRectGraphicsItem.h"
#include "MyRotatedRectGraphicsItem.h"
#include "MyOvalGraphicsItem.h"
#include "MyCircleGraphicsItem.h"
#include "MyRingGraphicsItem.h"
#include "MyPolygonGraphicsItem.h"
#include "MyTestPaintItem.h"

#include "ImageProcessManager.h"

MainWindow::MainWindow() :
	m_scene(new MyGraphicsScene(QRectF(QPointF(0, 0), QPointF(600, 600)), this)),
	m_view(new MyGraphicsView(m_scene))
{
	QFont font("Arial", 14, QFont::Bold);
	m_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	m_combobox = new QComboBox;
	m_combobox->addItem("rectangle");
	m_combobox->addItem("rotated rectangle");
	m_combobox->addItem("circle");
	m_combobox->addItem("oval");
	m_combobox->addItem("ring");
	m_combobox->addItem("arc");
	m_combobox->addItem("polygon");
	m_combobox->setFont(font);

	QHBoxLayout* hLayout = new QHBoxLayout;
	m_addImageButton = new QPushButton("add image");
	m_addImageButton->setFont(font);
	connect(m_addImageButton, &QPushButton::clicked, this, &MainWindow::onAddImage);
	m_clearButton = new QPushButton("clear");
	m_clearButton->setFont(font);
	connect(m_clearButton, &QPushButton::clicked, [this] {
		m_scene->setPixmapItem(nullptr);
		m_scene->clear();
		});

	QVBoxLayout* vLayout = new QVBoxLayout;
	m_addImageButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	vLayout->addWidget(m_addImageButton);
	m_combobox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	vLayout->addWidget(m_combobox);
	m_clearButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	vLayout->addWidget(m_clearButton);

	QWidget* vLayoutWidget = new QWidget(this);
	vLayoutWidget->setLayout(vLayout);

	m_binaryButton = new QPushButton("binary");
	connect(m_binaryButton, &QPushButton::clicked,
		[] {
			ImageProcessManager::getInstance().setThresholdType(THRESH_BINARY);
		});
	m_binaryInvertedButton = new QPushButton("binary inverted");
	connect(m_binaryInvertedButton, &QPushButton::clicked,
		[] {
			ImageProcessManager::getInstance().setThresholdType(THRESH_BINARY_INV);
		});
	m_thresholdTruncatedButton = new QPushButton("truncate");
	connect(m_thresholdTruncatedButton, &QPushButton::clicked,
		[] {
			ImageProcessManager::getInstance().setThresholdType(THRESH_TRUNC);
		});
	m_thresholdToZeroButton = new QPushButton("threshold to zero");
	connect(m_thresholdToZeroButton, &QPushButton::clicked,
		[] {
			ImageProcessManager::getInstance().setThresholdType(THRESH_TOZERO);
		});
	m_thresholdToZeroInvertedButton = new QPushButton("threshold to zero inverted");
	connect(m_thresholdToZeroInvertedButton, &QPushButton::clicked,
		[] {
			ImageProcessManager::getInstance().setThresholdType(THRESH_TOZERO_INV);
		});
	m_slider = new QSlider;
	m_slider->setRange(0, 255);
	connect(m_slider, &QSlider::valueChanged, [](int value) {
		ImageProcessManager::getInstance().setThresh(value);
		});

	auto path = qApp->applicationDirPath();
	m_slider->setOrientation(Qt::Horizontal);

	QVBoxLayout* vRightLayout = new QVBoxLayout;
	m_binaryButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	vRightLayout->addWidget(m_binaryButton, 1);
	m_binaryInvertedButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	vRightLayout->addWidget(m_binaryInvertedButton, 1);
	m_thresholdTruncatedButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	vRightLayout->addWidget(m_thresholdTruncatedButton, 1);
	m_thresholdToZeroButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	vRightLayout->addWidget(m_thresholdToZeroButton, 1);
	m_thresholdToZeroInvertedButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	vRightLayout->addWidget(m_thresholdToZeroInvertedButton, 1);
	m_slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	vRightLayout->addWidget(m_slider, 4);

	QWidget* gridWidget = new QWidget;
	gridWidget->setLayout(vRightLayout);

	QSplitter* splitter = new QSplitter(this);
	splitter->addWidget(vLayoutWidget);
	splitter->addWidget(m_view);
	splitter->addWidget(gridWidget);

	this->setCentralWidget(splitter);

	connect(m_combobox, QOverload<int>::of(&QComboBox::currentIndexChanged),
		this, &MainWindow::onShapeSelectionChanged);
}

void MainWindow::onAddImage() {
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
	if (fileName.isEmpty())
		return;
	m_scene->clear();
	auto item = m_scene->addPixmap(QPixmap(fileName));
	m_scene->setPixmapItem(item);
	connect(&ImageProcessManager::getInstance(), &ImageProcessManager::newImage,
		this, [this](QPixmap pixmap) { dynamic_cast<QGraphicsPixmapItem*>(m_scene->pixmapItem())->setPixmap(pixmap); });
	m_scene->pixmapItem()->setFlags(QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsFocusable
		| QGraphicsItem::ItemIsSelectable);
	ImageProcessManager::getInstance().setImage(fileName);
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
		item = new RingGraphicsItem(nullptr);
		m_scene->setState(MyGraphicsScene::ForRingLeftPress);
		connect(dynamic_cast<RingGraphicsItem*>(item), &RingGraphicsItem::changeSceneToGetRingLeftPressAndHoverPoint, m_scene, &MyGraphicsScene::onChangeSceneToGetRingLeftPressAndHoverPoint);
		connect(dynamic_cast<RingGraphicsItem*>(item), &RingGraphicsItem::changeSceneToGetRingRightPressAndHoverPoint, m_scene, &MyGraphicsScene::onChangeSceneToGetRingRightPressAndHoverPoint);
		connect(m_scene, &MyGraphicsScene::newLeftPressedPoint, dynamic_cast<RingGraphicsItem*>(item), &RingGraphicsItem::onNewLeftPressedPoint);
		connect(m_scene, &MyGraphicsScene::newHoveredPoint, dynamic_cast<RingGraphicsItem*>(item), &RingGraphicsItem::onNewHoveredPoint);
		connect(m_scene, &MyGraphicsScene::newRightPressedPoint, dynamic_cast<RingGraphicsItem*>(item), &RingGraphicsItem::onNewRightPressedPoint);
	}
	break;
	case 5:
		//TODO: Arc Item
		item = new MyTestPaintItem(nullptr, 300, 300);
		break;
	case 6:
	{
		item = new PolygonGraphicsItem(nullptr);
		m_scene->setState(MyGraphicsScene::ForPolygonLeftRightHover);
		connect(m_scene, &MyGraphicsScene::newLeftPressedPoint, dynamic_cast<PolygonGraphicsItem*>(item), &PolygonGraphicsItem::onNewLeftPressedPoint);
		connect(m_scene, &MyGraphicsScene::newHoveredPoint, dynamic_cast<PolygonGraphicsItem*>(item), &PolygonGraphicsItem::onNewHoveredPoint);
		connect(m_scene, &MyGraphicsScene::newRightPressedPoint, dynamic_cast<PolygonGraphicsItem*>(item), &PolygonGraphicsItem::onNewRightPressedPoint);
	}
	break;
	default:
		break;
	}
	if (item) {
		m_scene->addItem(item);
	}
}