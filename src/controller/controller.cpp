#include "controller.h"

namespace atlas {

Controller::Controller(std::unique_ptr<Model> model, std::unique_ptr<View> view, std::unique_ptr<Filter> filter)
{
	model_ = std::move(model);
	view_ = std::move(view);
	filter_ = std::move(filter);
}



void Controller::MainLoop(int argc, char* argv[])
{
	std::thread view_thread(&View::MainLoop, view_.get(), argc, argv);
	view_thread.detach();

	std::thread model_thread(&Model::MainLoop, model_.get(), argc, argv);
	model_thread.detach();

	std::unique_ptr<PositionData> position_data;
	std::unique_ptr<VisualizationData> visual_data;
	std::unique_ptr<ProcessedSensorData> sensor_data;
	std::shared_ptr<CalibrationData> calibration_data;
	std::unique_ptr<ProcessedOdometryData> odometry_data;

	sensor_data = model_->GetSensorData();
	odometry_data = model_->GetOdometryData();
	calibration_data = model_->GetCalibrationData();

	filter_->Initialize(calibration_data, std::move(odometry_data), std::move(sensor_data));

	while (true) {
		sensor_data = model_->GetSensorData();
		odometry_data = model_->GetOdometryData();
		position_data = filter_->FilterStep(std::move(odometry_data), std::move(sensor_data));
	}
}

} // namespace atlas
