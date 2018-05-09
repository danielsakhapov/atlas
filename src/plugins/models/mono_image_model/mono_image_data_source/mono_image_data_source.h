#ifndef MONO_IMAGE_DATA_SOURCE_H
#define MONO_IMAGE_DATA_SOURCE_H

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

#include "data_source.h"

#include "raw_sensor_data.h"
#include "mono_image_calibration_data.h"
#include "mono_image_raw_odometry_data.h"

class MonoImageDataSource final : public atlas::DataSource
{
public:
	MonoImageDataSource(size_t n_cap, double f, cv::Point2d pp);
	MonoImageDataSource(const std::string& dir, double f, cv::Point2d pp);
	~MonoImageDataSource() = default;

	void MainLoop() final;
	void Initialize() final;

private:
	size_t n_cap_;
	bool realtime_;
	size_t n_frame_;
	std::string dir_;
	cv::VideoCapture cap_;
	std::vector<cv::String> filenames_;
};

#endif // MONO_IMAGE_DATA_SOURCE_H
