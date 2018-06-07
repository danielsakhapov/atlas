#ifndef MONO_IMAGE_POSITION_DATA_H
#define MONO_IMAGE_POSITION_DATA_H

#include <opencv2/opencv.hpp>

#include "position_data.h"

struct MonoImagePositionData : PositionData
{
    cv::Mat R;
    cv::Mat t;

    MonoImagePositionData(
        cv::Mat R, 
        cv::Mat t);
};

#endif // MONO_IMAGE_POSITION_DATA_H
