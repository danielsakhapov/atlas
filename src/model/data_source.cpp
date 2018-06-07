#include "data_source.h"

namespace atlas {

bool DataSource::IsSensorDataLeft() const
{
    return is_sensor_data_left_ || !sensor_data_queue_.empty();
}

bool DataSource::IsOdometryDataLeft() const
{
    return is_odometry_data_left_ || !odometry_data_queue_.empty();
}

bool DataSource::IsCalibrationDataEmpty() const
{
    return !static_cast<bool>(calibration_data_);
}

std::unique_ptr<RawSensorData> DataSource::GetSensorData()
{
    std::unique_ptr<RawSensorData> p = nullptr;

    if (!IsSensorDataLeft()) {
        Logger::Warning({"data source has no sensor data left while calling DataSource::GetSensorData"});
    }

    std::unique_lock<std::mutex> lck(sensor_data_mutex_);
    sensor_data_cond_var_.wait(lck, [&] { return !sensor_data_queue_.empty(); });
    p = std::move(sensor_data_queue_.front());
    sensor_data_queue_.pop();

    return p;
}

std::unique_ptr<RawOdometryData> DataSource::GetOdometryData()
{
    std::unique_ptr<RawOdometryData> p = nullptr;

    if (!IsOdometryDataLeft()) {
        Logger::Warning({"data source has no odometry data left while calling DataSource::GetOdometryData"});
    }

    std::unique_lock<std::mutex> lck(odometry_data_mutex_);
    odometry_data_cond_var_.wait(lck, [&] { return !odometry_data_queue_.empty(); });
    p = std::move(odometry_data_queue_.front());
    odometry_data_queue_.pop();

    return p;
}

std::shared_ptr<CalibrationData> DataSource::GetCalibrationData()
{
    if (!calibration_data_) {
        Logger::Warning({"calibration data is nullptr while calling DataSource::GetCalibrationData"});
    }
    
    return calibration_data_;
}

} // namespace atlas
