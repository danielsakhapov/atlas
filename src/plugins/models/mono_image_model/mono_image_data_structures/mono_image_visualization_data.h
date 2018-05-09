#ifndef MONO_IMAGE_VISUALIZATION_DATA_H
#define MONO_IMAGE_VISUALIZATION_DATA_H

#include <opencv2/opencv.hpp>

#include "visualization_data.h"

struct MonoImageVisualizationData : VisualizationData
{
	MonoImageVisualizationData(cv::Mat frame);
	cv::Mat frame;
};

#endif // MONO_IMAGE_VISUALIZATION_DATA_H
