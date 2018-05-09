#include "data_source.h"

namespace atlas {

bool DataSource::OutOfSensorData() const
{
	return out_of_sensor_data_ && sensor_data_queue_.empty();
}



bool DataSource::OutOfOdometryData() const
{
	return out_of_odometry_data_ && odometry_data_queue_.empty();
}



std::unique_ptr<RawSensorData> DataSource::GetSensorData()
{
	if (!OutOfSensorData()) {
		std::unique_lock<std::mutex> lck(sensor_data_mutex_);
		sensor_data_cond_var_.wait(lck, [&] { return !sensor_data_queue_.empty(); });
		auto p = std::move(sensor_data_queue_.front());
		sensor_data_queue_.pop();
		return p;
	}

	Logger::Warning({"data source has no sensor data left while calling DataSource::GetSensorData"});
	return nullptr;
}



std::unique_ptr<RawOdometryData> DataSource::GetOdometryData()
{
	if (!OutOfOdometryData()) {
		std::unique_lock<std::mutex> lck(odometry_data_mutex_);
		odometry_data_cond_var_.wait(lck, [&] { return !odometry_data_queue_.empty(); });
		auto p = std::move(odometry_data_queue_.front());
		odometry_data_queue_.pop();
		return p;
	}

	Logger::Warning({"data source has no odometry data left while calling DataSource::GetOdometryData"});
	return nullptr;
}



std::shared_ptr<CalibrationData> DataSource::GetCalibrationData()
{
	return calibration_data_;
}

} // namespace atlas
