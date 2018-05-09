#ifndef MONO_IMAGE_DATA_PROCESSOR_H
#define MONO_IMAGE_DATA_PROCESSOR_H

#include <memory>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

#include "logger.hpp"
#include "data_processor.h"

#include "raw_sensor_data.h"
#include "processed_sensor_data.h"
#include "mono_image_calibration_data.h"
#include "mono_image_raw_odometry_data.h"
#include "mono_image_processed_odometry_data.h"

class MonoImageDataProcessor : public atlas::DataProcessor
{
public:
	MonoImageDataProcessor() = default;
	~MonoImageDataProcessor() = default;
	
	std::unique_ptr<ProcessedSensorData> ProcessSensorData(std::unique_ptr<RawSensorData> data) const;
	std::unique_ptr<ProcessedOdometryData> ProcessOdometryData(std::unique_ptr<RawOdometryData> data) const;

private:
	double f_;
	cv::Point2d pp_;
};

#endif // MONO_IMAGE_DATA_PROCESSOR_H
