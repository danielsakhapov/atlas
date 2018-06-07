#include "model.h"
#include "mono_image_processed_odometry_data.h"

namespace atlas {

void Model::MainLoop(
    int, 
    char*[])
{
    auto cd = data_source_->GetCalibrationData();
    data_processor_->SetCalibrationData(cd);
    data_storage_.SetCalibrationData(cd);

    while (data_source_->IsSensorDataLeft() || data_source_->IsOdometryDataLeft()) {
        if (data_source_->IsSensorDataLeft()) {
            auto p = data_source_->GetSensorData();
            auto pp = data_processor_->ProcessSensorData(std::move(p));
            data_storage_.PushSensorData(std::move(pp));
        }
        else {
            data_storage_.SetNoSensorDataLeft();
        }

        if (data_source_->IsOdometryDataLeft()) {
            auto p = data_source_->GetOdometryData();
            auto pp = data_processor_->ProcessOdometryData(std::move(p));
            data_storage_.PushOdometryData(std::move(pp));
        }
        else {
            data_storage_.SetNoOdometryDataLeft();
        }
    }

    data_storage_.SetNoSensorDataLeft();
    data_storage_.SetNoOdometryDataLeft();
}

bool Model::IsSensorDataLeft() const
{
    return data_storage_.IsSensorDataLeft();
}

bool Model::IsOdometryDataLeft() const
{
    return data_storage_.IsOdometryDataLeft();
}

bool Model::IsCalibrationDataEmpty() const
{
    return data_storage_.IsCalibrationDataEmpty();
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
