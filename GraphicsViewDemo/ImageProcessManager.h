#pragma once
#include <QString>
#include <QPixmap>
#include <QPainterPath>
#include <QObject>

#include "opencv_dependencies.h"

class ImageProcessManager : public QObject
{
	Q_OBJECT
public:
	enum class ImageProcessType {
		None,
		Threshold,
		ContrastAndBrightness
	};
public:
	static ImageProcessManager& getInstance() {
		static ImageProcessManager manager;
		return manager;
	}
private:
	ImageProcessManager();
public:
	ImageProcessManager(ImageProcessManager const&) = delete;
	void operator=(ImageProcessManager const&) = delete;
public:
	void setImage(const QString& name);
	void setImage(const QImage& image);
	void setProcessType(ImageProcessType type) { m_processType = type; }
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
	void convertImageToMat(const QImage& image, cv::OutputArray&) const;
	cv::Mat createMaskFromPath(const QPainterPath&) const;

	cv::Mat thresholdProcess() const;
signals:
	void newImage(QPixmap pixmap);
private:
	Mat m_source;
	QPixmap m_pixmap;
	ThresholdTypes m_thresholdType;
	int m_threshValue;
	QPainterPath m_path;
	ImageProcessType m_processType;
};

