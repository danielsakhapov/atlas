#ifndef MONO_IMAGE_SENSOR_FILTER_H
#define MONO_IMAGE_SENSOR_FILTER_H

#include <memory>

#include <opencv2/opencv.hpp>

#include "logger.hpp"
#include "sensor_filter.h"

#include "processed_sensor_data.h"
#include "mono_image_calibration_data.h"

class MonoImageSensorFilter final : public atlas::SensorFilter
{
public:
	MonoImageSensorFilter() = default;
	~MonoImageSensorFilter() = default;

	virtual void Initialize(
		std::shared_ptr<CalibrationData> calibration_data,
		std::unique_ptr<ProcessedSensorData> sensor_data) final;
	virtual std::unique_ptr<PositionData> FilterStep(std::unique_ptr<ProcessedSensorData> data) final;

private:
	double f_;
	cv::Point2d pp_;
};

#endif // MONO_IMAGE_SENSOR_FILTER_H
