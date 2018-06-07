#include "data_storage.h"

namespace atlas {

DataStorage::DataStorage()
{
    is_sensor_data_left_ = true;
    is_odometry_data_left_ = true;
}

void DataStorage::SetNoSensorDataLeft()
{
    is_sensor_data_left_ = false;
}

void DataStorage::SetNoOdometryDataLeft()
{
    is_odometry_data_left_ = false;
}

bool DataStorage::IsSensorDataLeft() const
{
    return is_sensor_data_left_ || !sensor_data_queue_.empty();
}

bool DataStorage::IsOdometryDataLeft() const
{
    return is_odometry_data_left_ || !odometry_data_queue_.empty();
}

bool DataStorage::IsCalibrationDataEmpty() const
{
    return !static_cast<bool>(calibration_data_);
}

void DataStorage::SetCalibrationData(
    std::shared_ptr<CalibrationData> data)
{
    if (!data) {
        Logger::Warning({"calibration data is nullptr while calling DataStorage::SetCalibrationData"});
    }

    calibration_data_ = data;
}

std::unique_ptr<ProcessedSensorData> DataStorage::GetSensorData()
{
    if (!IsSensorDataLeft()) {
        Logger::Debug({"data storage has no sensor data left while calling DataStorage::GetSensorData so return nullptr"});
        return nullptr;
    }

    std::unique_lock<std::mutex> lck(sensor_data_mutex_);
    sensor_data_cond_var_.wait(lck, [&] { return !sensor_data_queue_.empty(); });
    auto p = std::move(sensor_data_queue_.front());
    sensor_data_queue_.pop();
    return p;
}

std::unique_ptr<ProcessedOdometryData> DataStorage::GetOdometryData()
{
    if (!IsOdometryDataLeft()) {
        Logger::Debug({"data storage has no odometry data left while calling DataStorage::GetOdometryData so return nullptr"});
        return nullptr;
    }

    std::unique_lock<std::mutex> lck(odometry_data_mutex_);
    odometry_data_cond_var_.wait(lck, [&] { return !odometry_data_queue_.empty(); });
    auto p = std::move(odometry_data_queue_.front());
    odometry_data_queue_.pop();
    return p;
}

std::shared_ptr<CalibrationData> DataStorage::GetCalibrationData()
{
    if (!calibration_data_) {
        Logger::Warning({"calibration data is nullptr while calling DataStorage::GetCalibrationData"});
    }

    return calibration_data_;
}

void DataStorage::PushSensorData(
    std::unique_ptr<ProcessedSensorData> data)
{
    if (!data) {
        Logger::Debug({"sensor data is nullptr while calling DataStorage::PushSensorData"});
    }

    sensor_data_mutex_.lock();
    sensor_data_queue_.emplace(std::move(data));
    sensor_data_mutex_.unlock();
    sensor_data_cond_var_.notify_all();
}

void DataStorage::PushOdometryData(
    std::unique_ptr<ProcessedOdometryData> data)
{
    if (!data) {
        Logger::Debug({"odometry data is nullptr while calling DataStorage::PushOdometryData"});
    }

    odometry_data_mutex_.lock();
    odometry_data_queue_.emplace(std::move(data));
    odometry_data_mutex_.unlock();
    odometry_data_cond_var_.notify_all();
}

} // namespace atlas
