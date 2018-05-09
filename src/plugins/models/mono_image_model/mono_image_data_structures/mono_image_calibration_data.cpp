#include "mono_image_calibration_data.h"

MonoImageCalibrationData::MonoImageCalibrationData(double f, cv::Point2d pp)
{
	this->f  = f;
	this->pp = pp;
}
