#include "controller.h"

namespace atlas {

Controller::Controller(
    std::unique_ptr<Model> model, 
    std::unique_ptr<View> view, 
    std::unique_ptr<Filter> filter,
    std::unique_ptr<Mapper> mapper)
{
    model_ = std::move(model);
    view_ = std::move(view);
    filter_ = std::move(filter);
    mapper_ = std::move(mapper);
}

void Controller::MainLoop(
    int argc, 
    char* argv[])
{
    std::thread view_thread(&View::MainLoop, view_.get(), argc, argv);
    view_thread.detach();

    std::thread model_thread(&Model::MainLoop, model_.get(), argc, argv);
    model_thread.detach();

    std::unique_ptr<PositionData> position_data;
    std::unique_ptr<VisualizationData> mapper_data;
    std::unique_ptr<ProcessedSensorData> sensor_data;
    std::shared_ptr<CalibrationData> calibration_data;
    std::unique_ptr<ProcessedOdometryData> odometry_data;
    std::unique_ptr<VisualizationData> sensor_visualization_data;
    std::unique_ptr<VisualizationData> odometry_visualization_data;

    sensor_data = model_->GetSensorData();
    odometry_data = model_->GetOdometryData();
    calibration_data = model_->GetCalibrationData();

    filter_->Initialize(calibration_data, std::move(sensor_data), std::move(odometry_data));

    while (model_->IsSensorDataLeft() || model_->IsOdometryDataLeft()) {
        sensor_data = model_->GetSensorData();
        odometry_data = model_->GetOdometryData();
        std::tie(position_data,
                 sensor_visualization_data,
                 odometry_visualization_data) = filter_->FilterStep(
                                                    std::move(sensor_data), 
                                                    std::move(odometry_data));
        mapper_->Update(std::move(position_data));
        mapper_data = mapper_->GetData();
        view_->Show(
            std::move(mapper_data),
            std::move(sensor_visualization_data),
            std::move(odometry_visualization_data));
    }
}

} // namespace atlas
