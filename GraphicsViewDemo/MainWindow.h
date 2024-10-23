#pragma once
#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QSlider>

#include "MyGraphicsScene.h"
#include "MyGraphicsView.h"

class MainWindow :
    public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
private slots:
    void onShapeSelectionChanged(int index);
    void onAddImage();
private:
    QComboBox* m_combobox;
    QPushButton* m_addImageButton;
    QPushButton* m_clearButton;
    MyGraphicsScene* m_scene;
    MyGraphicsView* m_view;
    QPushButton* m_binaryButton;
    QPushButton* m_binaryInvertedButton;
    QPushButton* m_thresholdTruncatedButton;
    QPushButton* m_thresholdToZeroButton;
    QPushButton* m_thresholdToZeroInvertedButton;
    QSlider* m_slider;
};
