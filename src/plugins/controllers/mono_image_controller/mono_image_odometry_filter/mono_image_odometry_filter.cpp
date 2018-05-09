#include "mono_image_odometry_filter.h"

void MonoImageOdometryFilter::Initialize(
	std::shared_ptr<CalibrationData> calibration_data,
	std::unique_ptr<ProcessedOdometryData> odometry_data)
{
	f_ = static_cast<MonoImageCalibrationData*>(calibration_data.get())->f;
	pp_ = static_cast<MonoImageCalibrationData*>(calibration_data.get())->pp;
	odometry_data_ = std::move(odometry_data);
}



std::unique_ptr<PositionData> MonoImageOdometryFilter::FilterStep(std::unique_ptr<ProcessedOdometryData> data)
{
	cv::Mat frame0, frame1, gray0, gray1, mask, R, t, E;

	frame0 = static_cast<MonoImageProcessedOdometryData*>(odometry_data_.get())->frame;
	frame1 = static_cast<MonoImageProcessedOdometryData*>(data.get())->frame;

	cv::cvtColor(frame0, gray0, cv::COLOR_BGR2GRAY);
	cv::cvtColor(frame1, gray1, cv::COLOR_BGR2GRAY);

	std::vector<cv::KeyPoint> key_points0;
	cv::FAST(gray0, key_points0, 20);

	std::vector<cv::Point2f> points0, points1;
	cv::KeyPoint::convert(key_points0, points0);

	std::vector<float> err;
	std::vector<unsigned char> status;
	std::vector<cv::Point2f> tmp_points0, tmp_points1;
	cv::calcOpticalFlowPyrLK(gray0, gray1, points0, points1, status, err);

	for (int i = 0; i < status.size(); ++i) {
		if (status[i]) {
			tmp_points0.push_back(points0[i]);
			tmp_points1.push_back(points1[i]);
		}
	}
	E = cv::findEssentialMat(tmp_points1, tmp_points0, f_, pp_, cv::RANSAC, 0.999, 1.0, mask);
	cv::recoverPose(E, tmp_points1, tmp_points0, R, t, f_, pp_, mask);

	return nullptr;
}