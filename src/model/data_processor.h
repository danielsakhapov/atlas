#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <memory>

#include "logger.hpp"

#include "raw_sensor_data.h"
#include "calibration_data.h"
#include "raw_odometry_data.h"
#include "processed_sensor_data.h"
#include "processed_odometry_data.h"

namespace atlas {

class DataProcessor
{
public:
	DataProcessor() = default;
	virtual ~DataProcessor() = default;

	void SetCalibrationData(std::shared_ptr<CalibrationData> data);
	virtual std::unique_ptr<ProcessedSensorData> ProcessSensorData(std::unique_ptr<RawSensorData> data) const = 0;
	virtual std::unique_ptr<ProcessedOdometryData> ProcessOdometryData(std::unique_ptr<RawOdometryData> data) const = 0;

protected:
	std::shared_ptr<CalibrationData> calibration_data_;
};

} // namespace atlas

#endif // DATA_PROCESSOR_H
