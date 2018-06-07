#include "mono_image_processed_odometry_data.h"

MonoImageProcessedOdometryData::MonoImageProcessedOdometryData(
    size_t id, 
    cv::Mat&& frame)
{
    this->id = id;
    this->frame = std::move(frame);
}
