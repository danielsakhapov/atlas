#ifndef ODOMETRY_FILTER_H
#define ODOMETRY_FILTER_H

#include <memory>

#include "position_data.h"
#include "calibration_data.h"
#include "processed_odometry_data.h"

namespace atlas {

class OdometryFilter
{
public:
	OdometryFilter() = default;
	virtual ~OdometryFilter() = default;

	virtual void Initialize(
		std::shared_ptr<CalibrationData> calibration_data,
		std::unique_ptr<ProcessedOdometryData> odomerty_data) = 0;
	virtual std::unique_ptr<PositionData> FilterStep(std::unique_ptr<ProcessedOdometryData> data) = 0;

protected:
	std::shared_ptr<CalibrationData> calibration_data_;
	std::unique_ptr<ProcessedOdometryData> odometry_data_;
};

} // namespace atlas

#endif // ODOMETRY_FILTER_H
