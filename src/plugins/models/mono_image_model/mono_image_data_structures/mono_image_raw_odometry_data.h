#ifndef MONO_IMAGE_RAW_ODOMETRY_DATA_H
#define MONO_IMAGE_RAW_ODOMETRY_DATA_H

#include <opencv2/opencv.hpp>

#include "raw_odometry_data.h"

struct MonoImageRawOdometryData : RawOdometryData
{
    cv::Mat frame;
    
    MonoImageRawOdometryData(
        size_t id, 
        cv::Mat&& frame);
};

#endif // MONO_IMAGE_RAW_ODOMETRY_DATA_H
