#include "mono_image_data_source.h"

MonoImageDataSource::MonoImageDataSource(size_t n_cap, double f, cv::Point2d pp)
{
	n_cap_ = n_cap;
	realtime_ = true;
	out_of_sensor_data_ = true;
	out_of_odometry_data_ = false;
	calibration_data_.reset(new MonoImageCalibrationData(f, pp));
}



MonoImageDataSource::MonoImageDataSource(const std::string& dir, double f, cv::Point2d pp)
{
	dir_ = dir;
	realtime_ = false;
	out_of_sensor_data_ = true;
	out_of_odometry_data_ = false;
	calibration_data_.reset(new MonoImageCalibrationData(f, pp));
}



void MonoImageDataSource::Initialize()
{
	n_frame_ = 0;
	if (realtime_) {
		cap_.open(n_cap_);
		if (!cap_.isOpened()) {
			atlas::Logger::FatalError({"can not open cap # " + n_cap_});
		}
	}
	else {
		cv::glob(dir_, filenames_);
		if (!filenames_.size()) {
			atlas::Logger::FatalError({"directory " + dir_ + " is empty"});
		}
	}

	std::thread main_loop_thread(&MonoImageDataSource::MainLoop, this);
	main_loop_thread.detach();
}



void MonoImageDataSource::MainLoop()
{
	if (realtime_) {
		odometry_data_mutex_.lock();
		cv::Mat frame;
		cap_ >> frame;
		odometry_data_mutex_.unlock();
		while (!frame.empty()) {
			// odometry_data_mutex_.lock();
			odometry_data_queue_.emplace(new MonoImageRawOdometryData(n_frame_++, std::move(frame)));
			// odometry_data_mutex_.unlock();
			odometry_data_cond_var_.notify_all();
			cap_ >> frame;
		}
	}
	else {
		while (n_frame_ < filenames_.size()) {
			// odometry_data_mutex_.lock();
			odometry_data_queue_.emplace(new MonoImageRawOdometryData(n_frame_, cv::imread(filenames_[n_frame_++])));
			// odometry_data_mutex_.unlock();
			odometry_data_cond_var_.notify_all();
		}
	}
	out_of_odometry_data_ = true;
}
