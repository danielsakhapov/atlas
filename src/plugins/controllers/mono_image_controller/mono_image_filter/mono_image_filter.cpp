#include "mono_image_filter.h"

void MonoImageFilter::Initialize(
	std::shared_ptr<CalibrationData> calibration_data,
	std::unique_ptr<ProcessedOdometryData> odometry_data,
	std::unique_ptr<ProcessedSensorData> sensor_data)
{
	calibration_data_ = calibration_data;

	odometry_filter_.reset(new MonoImageOdometryFilter());
	odometry_filter_->Initialize(calibration_data, std::move(odometry_data));
}



std::unique_ptr<PositionData> MonoImageFilter::FilterStep(
	std::unique_ptr<ProcessedOdometryData> odometry_data,
	std::unique_ptr<ProcessedSensorData> sensor_data)
{
	auto odometry_pos = odometry_filter_->FilterStep(std::move(odometry_data));
	return nullptr;
}
