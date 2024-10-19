#pragma once
#include "opencv_dependencies.h"

#include <QString>
#include <QPixmap>
#include <QPainterPath>
#include <QObject>

class ImageProcessManager : public QObject
{
	Q_OBJECT
public:
	static ImageProcessManager& getInstance() {
		static ImageProcessManager manager;
		return manager;
	}
private:
	ImageProcessManager(){}
public:
	ImageProcessManager(ImageProcessManager const&) = delete;
	void operator=(ImageProcessManager const&) = delete;
public:
	void setImage(const QString& name);
	void setImage(const QImage& image);
	void setThresholdType(ThresholdTypes type) { 
		m_thresholdType = type; 
		processArea(m_path);
	}
	void setThresh(int value) {
		if (value > 255) {
			value = 255;
		}
		else if (value < 0) {
			value = 0;
		}
		m_threshValue = value;
		processArea(m_path);
	}
	void processArea(const QPainterPath& path);
private:
	void convertImageToMat(const QImage& image, cv::OutputArray&);
signals:
	void newImage(QPixmap pixmap);
private:
	Mat m_source;
	QPixmap m_pixmap;
	ThresholdTypes m_thresholdType;
	int m_threshValue;
	QPainterPath m_path;
};

