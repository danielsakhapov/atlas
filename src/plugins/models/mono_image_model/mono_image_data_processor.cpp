#include "mono_image_data_processor.h"

std::unique_ptr<ProcessedSensorData> MonoImageDataProcessor::ProcessSensorData(
    std::unique_ptr<RawSensorData>) const
{
    atlas::Logger::Debug({"calling of empty MonoImageDataProcessor::ProcessSensorData always return nullptr"});
    return nullptr;
}

std::unique_ptr<ProcessedOdometryData> MonoImageDataProcessor::ProcessOdometryData(
    std::unique_ptr<RawOdometryData> data) const
{
    // double f_ = (static_cast<MonoImageCalibrationData*>((calibration_data_.get())))->f;
    // cv::Point2f pp_ = (static_cast<MonoImageCalibrationData*>((calibration_data_.get())))->pp;
    if (data) {
        auto frame = static_cast<MonoImageRawOdometryData*>(data.get())->frame;
        return std::unique_ptr<ProcessedOdometryData>(new MonoImageProcessedOdometryData(data->id, std::move(frame)));
    }
    else {
        atlas::Logger::FatalError({"odometry data is empty while calling MonoImageDataProcessor::ProcessOdometryData"});
    }
}
