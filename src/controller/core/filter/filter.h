#ifndef FILTER_H
#define FILTER_H

#include <memory>

#include "logger.hpp"
#include "sensor_filter.h"
#include "odometry_filter.h"

#include "position_data.h"
#include "calibration_data.h"
#include "processed_sensor_data.h"
#include "processed_odometry_data.h"

namespace atlas {

class Filter
{
public:
	Filter() = default;
	virtual ~Filter() = default;

	virtual void Initialize(
		std::shared_ptr<CalibrationData> calibration_data,
		std::unique_ptr<ProcessedOdometryData> odometry_data,
		std::unique_ptr<ProcessedSensorData> sensor_data) = 0;
	virtual std::unique_ptr<PositionData> FilterStep(
		std::unique_ptr<ProcessedOdometryData> odometry_data,
		std::unique_ptr<ProcessedSensorData> sensor_data) = 0;

protected:
	std::unique_ptr<SensorFilter> sensor_filter_;
	std::unique_ptr<OdometryFilter> odometry_filter_;

	std::shared_ptr<CalibrationData> calibration_data_;
};

} // namespace atlas

#endif // FILTER_H
