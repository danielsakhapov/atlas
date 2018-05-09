#include "image_widget.h"

namespace atlas_ui {

ImageWidget::ImageWidget(QWidget* parent) : 
	QWidget(parent), 
	window_width_(0), 
	window_height_(0)
{}



void ImageWidget::ShowImage(const QImage& img)
{
	data_mutex_.lock();
	image_ = img.copy();
	data_mutex_.unlock();
	update();
}



void ImageWidget::paintEvent(QPaintEvent*)
{
	if (!image_.isNull()) {
		data_mutex_.lock();
		QImage temp_image = image_.scaled(width(), height());
		painter_.begin(this);
		painter_.drawImage(QPoint(0,0), temp_image);
		painter_.end();
		data_mutex_.unlock();
	}
}



void ImageWidget::ResizeLayout(const QSize& size)
{
	data_mutex_.lock();
	if (!window_width_) window_width_ = size.width();
	if (!window_height_) window_height_ = size.height();
	int dx = size.width() - window_width_;
	int dy = size.height() - window_height_;
	resize(width() + dx, height() + dy);
	window_width_ = size.width();
	window_height_ = size.height();
	data_mutex_.unlock();
	update();
}

}