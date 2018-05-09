#include "data_storage.h"

namespace atlas {

bool DataStorage::SensorDataEmpty() const
{
	return sensor_data_queue_.empty();
}



bool DataStorage::OdometryDataEmpty() const
{
	return odometry_data_queue_.empty();
}



bool DataStorage::CalibrationDataEmpty() const
{
	return static_cast<bool>(calibration_data_);
}



void DataStorage::SetCalibrationData(std::shared_ptr<CalibrationData> data)
{
	if (data) {
		calibration_data_ = data;
	}
	else {
		Logger::FatalError({"calibration data is empty while calling DataStorage::SetCalibrationData"});
	}
}



std::unique_ptr<ProcessedSensorData> DataStorage::GetSensorData()
{
	std::unique_lock<std::mutex> lck(sensor_data_mutex_);
	sensor_data_cond_var_.wait(lck, [&] { return !sensor_data_queue_.empty(); });
	auto p = std::move(sensor_data_queue_.front());
	sensor_data_queue_.pop();
	return p;
}



std::unique_ptr<ProcessedOdometryData> DataStorage::GetOdometryData()
{
	std::unique_lock<std::mutex> lck(odometry_data_mutex_);
	odometry_data_cond_var_.wait(lck, [&] { return !odometry_data_queue_.empty(); });
	auto p = std::move(odometry_data_queue_.front());
	odometry_data_queue_.pop();
	return p;
}



std::shared_ptr<CalibrationData> DataStorage::GetCalibrationData()
{
	return calibration_data_;
}



void DataStorage::PushSensorData(std::unique_ptr<ProcessedSensorData> data)
{
	if (data) {
		sensor_data_mutex_.lock();
		sensor_data_queue_.emplace(std::move(data));
		sensor_data_mutex_.unlock();
		sensor_data_cond_var_.notify_all();
	}
	else {
		Logger::Warning({"sensor data is empty while calling DataStorage::PushSensorData"});
	}
}



void DataStorage::PushOdometryData(std::unique_ptr<ProcessedOdometryData> data)
{
	if (data) {
		odometry_data_mutex_.lock();
		odometry_data_queue_.emplace(std::move(data));
		odometry_data_mutex_.unlock();
		odometry_data_cond_var_.notify_all();
	}
	else {
		Logger::Warning({"odometry data is empty while calling DataStorage::PushOdometryData"});
	}
}

} // namespace atlas
