#include "mono_image_raw_odometry_data.h"

MonoImageRawOdometryData::MonoImageRawOdometryData(size_t id, cv::Mat&& frame)
{
	this->id = id;
	this->frame = std::move(frame);
}
