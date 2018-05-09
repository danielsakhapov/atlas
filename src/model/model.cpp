#include "model.h"

namespace atlas {

void Model::MainLoop(int, char*[])
{
	auto cd = data_source_->GetCalibrationData();
	data_processor_->SetCalibrationData(cd);
	data_storage_.SetCalibrationData(cd);

	while (!data_source_->OutOfOdometryData() || !data_source_->OutOfSensorData()) {
		if (!data_source_->OutOfOdometryData()) {
			auto p = data_source_->GetOdometryData();
			auto pp = data_processor_->ProcessOdometryData(std::move(p));
			data_storage_.PushOdometryData(std::move(pp));
		}

		if (!data_source_->OutOfSensorData()) {
			auto p = data_source_->GetSensorData();
			auto pp = data_processor_->ProcessSensorData(std::move(p));
			data_storage_.PushSensorData(std::move(pp));
		}
	}
}



bool Model::SensorDataEmpty() const
{
	return data_storage_.SensorDataEmpty();
}



bool Model::OdometryDataEmpty() const
{
	return data_storage_.OdometryDataEmpty();
}



bool Model::CalibrationDataEmpty() const
{
	return data_storage_.CalibrationDataEmpty();
}



std::unique_ptr<ProcessedSensorData> Model::GetSensorData()
{
	return data_storage_.GetSensorData();
}



std::unique_ptr<ProcessedOdometryData> Model::GetOdometryData()
{
	return data_storage_.GetOdometryData();
}



std::shared_ptr<CalibrationData> Model::GetCalibrationData()
{
	return data_storage_.GetCalibrationData();
}

} // namespace atlas
