#ifndef DATA_SOURCE_H
#define DATA_SOURCE_H

#include <mutex>
#include <queue>
#include <memory>
#include <thread>
#include <condition_variable>

#include "logger.hpp"

#include "raw_sensor_data.h"
#include "calibration_data.h"
#include "raw_odometry_data.h"

namespace atlas {

class DataSource
{
public:
    DataSource() = default;
    virtual ~DataSource() = default;

    virtual void MainLoop() = 0;
    virtual void Initialize() = 0;

    bool IsSensorDataLeft() const;
    bool IsOdometryDataLeft() const;
    bool IsCalibrationDataEmpty() const;

    std::unique_ptr<RawSensorData> GetSensorData();
    std::unique_ptr<RawOdometryData> GetOdometryData();
    std::shared_ptr<CalibrationData> GetCalibrationData();

protected:
    bool is_sensor_data_left_;
    bool is_odometry_data_left_;

    std::mutex sensor_data_mutex_;
    std::mutex odometry_data_mutex_;
    std::condition_variable_any sensor_data_cond_var_;
    std::shared_ptr<CalibrationData> calibration_data_;
    std::condition_variable_any odometry_data_cond_var_;

    std::queue<std::unique_ptr<RawSensorData>> sensor_data_queue_;
    std::queue<std::unique_ptr<RawOdometryData>> odometry_data_queue_;
};

} // namespace atlas

#endif // DATA_SOURCE_H
