#ifndef MONO_IMAGE_ODOMETRY_FILTER_H
#define MONO_IMAGE_ODOMETRY_FILTER_H

#include <memory>

#include <opencv2/opencv.hpp>

#include "logger.hpp"
#include "odometry_filter.h"

#include "mono_image_calibration_data.h"
#include "mono_image_processed_odometry_data.h"

class MonoImageOdometryFilter final : public atlas::OdometryFilter
{
public:
	MonoImageOdometryFilter() = default;
	~MonoImageOdometryFilter() = default;

	virtual void Initialize(
		std::shared_ptr<CalibrationData> calibration_data,
		std::unique_ptr<ProcessedOdometryData> odomerty_data) final;
	virtual std::unique_ptr<PositionData> FilterStep(std::unique_ptr<ProcessedOdometryData> data) final;

private:
	double f_;
	cv::Mat R_;
	cv::Mat t_;
	cv::Point2d pp_;
};

#endif // MONO_IMAGE_ODOMETRY_FILTER_H
