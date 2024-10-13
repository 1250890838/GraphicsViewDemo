#pragma once
#include <qmainwindow.h>

#include <QComboBox>
#include <QPushButton>

#include "MyGraphicsScene.h"
#include "MyGraphicsView.h"
class MainWindow :
    public QMainWindow
{
public:
    MainWindow();
private slots:
    void onShapeSelectionChanged(int index);
    void onAddImage();
private:
    QComboBox* m_combobox;
    QPushButton* m_addImageButton;
    MyGraphicsScene* m_scene;
    MyGraphicsView* m_view;
    QGraphicsItem* m_currItem;
};

