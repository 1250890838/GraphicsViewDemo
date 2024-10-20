#include "ImageProcessManager.h"

#include <QImage>
#include <QPainter>

void ImageProcessManager::setImage(const QString& name)
{
	QImage image(name);
	setImage(image);
}

void ImageProcessManager::setImage(const QImage& image)
{
    m_pixmap=QPixmap::fromImage(image);
	Mat mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
    convertImageToMat(image, m_source);
}

void ImageProcessManager::processArea(const QPainterPath& p)
{
    if (m_source.empty()) return;

    m_path = p;
    Mat source;
    cvtColor(m_source, source, COLOR_BGR2GRAY);
    QImage maskImage(source.cols, source.rows, QImage::Format_Grayscale8);
    maskImage.fill(Qt::color0);
    QPainter painter(&maskImage);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::SolidPattern);
    painter.setPen(Qt::NoPen);
    painter.drawPath(p);
    painter.end();
    Mat mask(maskImage.height(), maskImage.width(), CV_8UC1, (uchar*)maskImage.bits(), maskImage.bytesPerLine());
    Mat antiMask;
    bitwise_not(mask, antiMask);
    Mat processedSource;
    threshold(source, processedSource, m_threshValue, 255, m_thresholdType);
    cvtColor(processedSource, processedSource, COLOR_GRAY2BGRA);
    Mat dest;
    processedSource.copyTo(dest, antiMask);
    bitwise_or(m_source, dest, dest, mask);
    QImage result(dest.data, dest.cols, dest.rows, dest.step[0], QImage::Format_ARGB32);
    emit newImage(QPixmap::fromImage(result));
}

void ImageProcessManager::convertImageToMat(const QImage& image,cv::OutputArray& out)
{
	switch (image.format()) 
	{
    case QImage::Format_Invalid:
    {
        cv::Mat empty;
        empty.copyTo(out);
        break;
    }
    case QImage::Format_RGB32:
    {
        cv::Mat view(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        view.copyTo(out);
        break;
    }
    case QImage::Format_RGB888:
    {
        cv::Mat view(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cvtColor(view, out, cv::COLOR_RGB2BGR);
        break;
    }
	}
}
