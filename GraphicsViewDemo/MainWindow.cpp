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
#include <QColorDialog>

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
	QFont font("Arial", 8, QFont::Bold);
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
	m_addImageButton = new QPushButton("Add image");
	m_addImageButton->setFont(font);
	connect(m_addImageButton, &QPushButton::clicked, this, &MainWindow::onAddImage);
	m_clearButton = new QPushButton("Clear");
	m_clearButton->setFont(font);
	connect(m_clearButton, &QPushButton::clicked, [this] {
		m_scene->setPixmapItem(nullptr);
		m_scene->clear();
		});

	QVBoxLayout* vLeftLayout = new QVBoxLayout;
	m_addImageButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	vLeftLayout->addWidget(m_addImageButton, 1, Qt::AlignHCenter);
	m_combobox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	vLeftLayout->addWidget(m_combobox, 1, Qt::AlignHCenter);
	m_clearButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	vLeftLayout->addWidget(m_clearButton, 1, Qt::AlignHCenter);
	vLeftLayout->addStretch(1);

	QWidget* leftWidget = new QWidget(this);
	leftWidget->setLayout(vLeftLayout);

	m_binaryButton = new QPushButton("Binary");
	m_binaryButton->setFont(font);
	connect(m_binaryButton, &QPushButton::clicked,
		[] {
			ImageProcessManager::getInstance().setThresholdType(THRESH_BINARY);
		});
	m_binaryInvertedButton = new QPushButton("Binary inverted");
	m_binaryInvertedButton->setFont(font);
	connect(m_binaryInvertedButton, &QPushButton::clicked,
		[] {
			ImageProcessManager::getInstance().setThresholdType(THRESH_BINARY_INV);
		});
	m_thresholdTruncatedButton = new QPushButton("Truncate");
	m_thresholdTruncatedButton->setFont(font);
	connect(m_thresholdTruncatedButton, &QPushButton::clicked,
		[] {
			ImageProcessManager::getInstance().setThresholdType(THRESH_TRUNC);
		});
	m_thresholdToZeroButton = new QPushButton("Threshold to zero");
	m_thresholdToZeroButton->setFont(font);
	connect(m_thresholdToZeroButton, &QPushButton::clicked,
		[] {
			ImageProcessManager::getInstance().setThresholdType(THRESH_TOZERO);
		});
	m_thresholdToZeroInvertedButton = new QPushButton("Threshold to zero inverted");
	m_thresholdToZeroInvertedButton->setFont(font);
	connect(m_thresholdToZeroInvertedButton, &QPushButton::clicked,
		[] {
			ImageProcessManager::getInstance().setThresholdType(THRESH_TOZERO_INV);
		});
	m_slider = new QSlider;
	m_slider->setRange(0, 255);
	connect(m_slider, &QSlider::valueChanged, [](int value) {
		ImageProcessManager::getInstance().setThresh(value);
		});
	m_slider->setOrientation(Qt::Horizontal);

	m_lineColorButton = new QPushButton;
	connect(m_lineColorButton, &QPushButton::clicked, this, &MainWindow::onLineColorButtonClicked);

	QVBoxLayout* vRightLayout = new QVBoxLayout;
	m_binaryButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	vRightLayout->addWidget(m_binaryButton, 1, Qt::AlignHCenter);
	m_binaryInvertedButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	vRightLayout->addWidget(m_binaryInvertedButton, 1, Qt::AlignHCenter);
	m_thresholdTruncatedButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	vRightLayout->addWidget(m_thresholdTruncatedButton, 1, Qt::AlignHCenter);
	m_thresholdToZeroButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	vRightLayout->addWidget(m_thresholdToZeroButton, 1, Qt::AlignHCenter);
	m_thresholdToZeroInvertedButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	vRightLayout->addWidget(m_thresholdToZeroInvertedButton, 1, Qt::AlignHCenter);
	m_slider->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	vRightLayout->addWidget(m_slider, 1, Qt::AlignHCenter);
	auto palette = m_lineColorButton->palette();
	palette.setColor(QPalette::Button, QColor(Qt::white));
	m_lineColorButton->setPalette(palette);
	m_lineColorButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	m_lineColorButton->setAutoFillBackground(true);
	m_lineColorButton->setFlat(false);
	vRightLayout->addWidget(m_lineColorButton, 1, Qt::AlignHCenter);
	vRightLayout->addStretch(1);

	QWidget* rightWidget = new QWidget;
	rightWidget->setLayout(vRightLayout);

	QSplitter* splitter = new QSplitter(this);
	splitter->addWidget(leftWidget);
	splitter->addWidget(m_view);
	splitter->addWidget(rightWidget);
	splitter->setStretchFactor(0, 0);
	splitter->setStretchFactor(1, 1);
	splitter->setStretchFactor(2, 0);

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
		[this](QPixmap pixmap) {
			dynamic_cast<QGraphicsPixmapItem*>(m_scene->pixmapItem())->setPixmap(pixmap); }
	);
	item->moveBy((m_scene->width() - item->boundingRect().width()) / 2, (m_scene->height() - item->boundingRect().height()) / 2);
	ImageProcessManager::getInstance().setImage(fileName);
}

void MainWindow::onLineColorButtonClicked()
{
	QColor selectedColor = QColorDialog::getColor();
	auto button=qobject_cast<QPushButton*>(sender());
	QPalette palette = button->palette();
	palette.setColor(QPalette::Button, selectedColor);
	palette.setColor(QPalette::Window, selectedColor);
	palette.setColor(QPalette::Base, selectedColor);
	button->setPalette(palette);
	button->update();
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
		m_scene->setState(MyGraphicsScene::ForLeftPress);
		break;
	case 3:
		item = new OvalGraphicsItem(nullptr, 200, 120);
		m_scene->setState(MyGraphicsScene::None);
		break;
	case 4:
		item = new RingGraphicsItem(nullptr);
		m_scene->setState(MyGraphicsScene::ForLeftPress);
		break;
	case 5:
		//TODO: Arc Item
		item = new MyTestPaintItem(nullptr, 300, 300);
		break;
	case 6:
		item = new PolygonGraphicsItem(nullptr);
		m_scene->setState(MyGraphicsScene::ForLeftPress | MyGraphicsScene::ForHover);
		break;
	default:
		break;
	}
	if (item) {
		connect(m_scene, &MyGraphicsScene::newLeftPressedPoint, item, &MyGraphicsItem::onNewLeftPressedPoint);
		connect(m_scene, &MyGraphicsScene::newHoveredPoint, item, &MyGraphicsItem::onNewHoveredPoint);
		connect(m_scene, &MyGraphicsScene::newRightPressedPoint, item, &MyGraphicsItem::onNewRightPressedPoint);
		item->setPen(QPen(m_lineColorButton->palette().color(QPalette::Button),10));
		m_scene->addItem(item);
	}
}