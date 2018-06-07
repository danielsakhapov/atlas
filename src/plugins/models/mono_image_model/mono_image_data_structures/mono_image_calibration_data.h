#ifndef MONO_IMAGE_CALIBRATION_DATA_H
#define MONO_IMAGE_CALIBRATION_DATA_H

#include <opencv2/opencv.hpp>

#include "calibration_data.h"

struct MonoImageCalibrationData : CalibrationData
{
    double f;
    cv::Point2d pp;

    MonoImageCalibrationData(
        double f, 
        cv::Point2d pp);
};

#endif // MONO_IMAGE_CALIBRATION_DATA_H
