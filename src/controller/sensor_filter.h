#ifndef SENSOR_FILTER_H
#define SENSOR_FILTER_H

#include <memory>

#include "position_data.h"
#include "calibration_data.h"
#include "visualization_data.h"
#include "processed_sensor_data.h"

namespace atlas {

class SensorFilter
{
public:
    SensorFilter() = default;
    virtual ~SensorFilter() = default;

    virtual void Initialize(
        std::shared_ptr<CalibrationData> calibration_data,
        std::unique_ptr<ProcessedSensorData> sensor_data) = 0;
    virtual std::tuple<
                std::unique_ptr<PositionData>,
                std::unique_ptr<VisualizationData>>
    FilterStep(
        std::unique_ptr<ProcessedSensorData> data) = 0;

protected:
    std::unique_ptr<ProcessedSensorData> prev_data_;
    std::shared_ptr<CalibrationData> calibration_data_;
};

} // namespace atlas

#endif // SENSOR_FILTER_H
