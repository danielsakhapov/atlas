#ifndef DATA_STORAGE_H
#define DATA_STORAGE_H

#include <mutex>
#include <queue>
#include <memory>
#include <condition_variable>

#include "logger.hpp"

#include "calibration_data.h"
#include "processed_sensor_data.h"
#include "processed_odometry_data.h"

namespace atlas {

class DataStorage
{
public:
    DataStorage();
    ~DataStorage() = default;

    void SetNoSensorDataLeft();
    void SetNoOdometryDataLeft();

    bool IsSensorDataLeft() const;
    bool IsOdometryDataLeft() const;
    bool IsCalibrationDataEmpty() const;

    std::unique_ptr<ProcessedSensorData> GetSensorData();
    std::shared_ptr<CalibrationData> GetCalibrationData();
    std::unique_ptr<ProcessedOdometryData> GetOdometryData();

    void SetCalibrationData(
        std::shared_ptr<CalibrationData> data);
    void PushSensorData(
        std::unique_ptr<ProcessedSensorData> data);
    void PushOdometryData(
        std::unique_ptr<ProcessedOdometryData> data);

private:
    bool is_sensor_data_left_;
	bool is_odometry_data_left_;

    std::mutex sensor_data_mutex_;
    std::mutex odometry_data_mutex_;
    std::mutex calibration_data_mutex_;

    std::condition_variable_any sensor_data_cond_var_;
    std::condition_variable_any odometry_data_cond_var_;

    std::shared_ptr<CalibrationData> calibration_data_;
    std::queue<std::unique_ptr<ProcessedSensorData>> sensor_data_queue_;
    std::queue<std::unique_ptr<ProcessedOdometryData>> odometry_data_queue_;
};

} // namespace atlas

#endif // DATA_STORAGE_H
