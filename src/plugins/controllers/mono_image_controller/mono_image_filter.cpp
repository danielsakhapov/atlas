#include "mono_image_filter.h"

void MonoImageFilter::Initialize(
    std::shared_ptr<CalibrationData> calibration_data,
    std::unique_ptr<ProcessedSensorData>,
    std::unique_ptr<ProcessedOdometryData> odometry_data)
{
    calibration_data_ = calibration_data;

    odometry_filter_.reset(new MonoImageOdometryFilter());
    odometry_filter_->Initialize(calibration_data, std::move(odometry_data));
}

std::tuple<
    std::unique_ptr<PositionData>,
    std::unique_ptr<VisualizationData>,
    std::unique_ptr<VisualizationData>>
MonoImageFilter::FilterStep(
    std::unique_ptr<ProcessedSensorData>,
    std::unique_ptr<ProcessedOdometryData> data)
{
    std::unique_ptr<PositionData> odometry_position_data;
    std::unique_ptr<VisualizationData> odometry_visualization_data;

    std::tie(odometry_position_data, 
                  odometry_visualization_data) = odometry_filter_->FilterStep(std::move(data));

    return std::make_tuple(std::move(odometry_position_data), nullptr, std::move(odometry_visualization_data));
}
