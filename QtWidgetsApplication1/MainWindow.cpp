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

MainWindow::MainWindow():
	m_scene(new MyGraphicsScene(QRectF(QPointF(0,0),QPointF(600,600)),this)),
	m_view(new MyGraphicsView(m_scene)),
	m_currItem(nullptr){

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
	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->addWidget(m_addImageButton);
	vLayout->addWidget(m_combobox);

	hLayout->addLayout(vLayout);
	hLayout->addWidget(m_view);

	QWidget* widget = new QWidget;
	widget->setLayout(hLayout);
	this->setCentralWidget(widget);

	connect(m_combobox, QOverload<int>::of(&QComboBox::currentIndexChanged), 
		this, &MainWindow::onShapeSelectionChanged);
}

void MainWindow::onAddImage(){
	QString fileName=QFileDialog::getOpenFileName(this,
		tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
	m_scene->clear();
	auto item=m_scene->addPixmap(QPixmap(fileName));
	item->setFlags(QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsFocusable
		| QGraphicsItem::ItemIsSelectable);
}

void MainWindow::onShapeSelectionChanged(int index) {
	RectGraphicsItem* item = nullptr;
	switch (index)
	{
	case 0:
		item = new RectGraphicsItem(nullptr, 200, 120);
		break;
	case 1:
		item = new RotatedRectGraphicsItem(nullptr, 200, 120);
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
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

