#ifndef MONO_IMAGE_PROCESSED_ODOMETRY_DATA_H
#define MONO_IMAGE_PROCESSED_ODOMETRY_DATA_H

#include <opencv2/opencv.hpp>

#include "processed_odometry_data.h"

struct MonoImageProcessedOdometryData : ProcessedOdometryData
{
    cv::Mat frame;

    MonoImageProcessedOdometryData(
        size_t id, 
        cv::Mat&& frame);
};

#endif // MONO_IMAGE_PROCESSED_ODOMETRY_DATA_H
