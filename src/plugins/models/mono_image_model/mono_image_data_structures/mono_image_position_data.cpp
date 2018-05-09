#include "mono_image_position_data.h"

MonoImagePositionData::MonoImagePositionData(cv::Mat R, cv::Mat t)
{
	this->R  = R;
	this->t = t;
}
