#include "mono_image_odometry_filter.h"

void MonoImageOdometryFilter::Initialize(
    std::shared_ptr<CalibrationData> calibration_data,
    std::unique_ptr<ProcessedOdometryData> odometry_data)
{
    f_ = static_cast<MonoImageCalibrationData*>(calibration_data.get())->f;
    pp_ = static_cast<MonoImageCalibrationData*>(calibration_data.get())->pp;
    frame0 = static_cast<MonoImageProcessedOdometryData*>(odometry_data.get())->frame;
    cv::cvtColor(frame0, gray0, cv::COLOR_BGR2GRAY);
    prev_data_ = std::move(odometry_data);

    R_ = cv::Mat(3, 3, CV_64FC1);
    t_ = cv::Mat(3, 1, CV_64FC1);

	t_.at<double>(0) = 0;
	t_.at<double>(1) = 0;
	t_.at<double>(2) = 0;

	R_.at<double>(0, 0) = 1; R_.at<double>(0, 1) = 0; R_.at<double>(0, 2) = 0;
	R_.at<double>(1, 0) = 0; R_.at<double>(1, 1) = 1; R_.at<double>(1, 2) = 0;
	R_.at<double>(2, 0) = 0; R_.at<double>(2, 1) = 0; R_.at<double>(2, 2) = 1;
}

std::tuple<
    std::unique_ptr<PositionData>,
    std::unique_ptr<VisualizationData>>
MonoImageOdometryFilter::FilterStep(
    std::unique_ptr<ProcessedOdometryData> data)
{
    frame1 = std::move(static_cast<MonoImageProcessedOdometryData*>(data.get())->frame);

    cv::cvtColor(frame1, gray1, cv::COLOR_BGR2GRAY);

    if (points0.size() < 500) {
        cv::FAST(gray0, key_points0, 20);
        cv::KeyPoint::convert(key_points0, points0);
    }

    cv::calcOpticalFlowPyrLK(gray0, gray1, points0, points1, status, err);

    tmp_points0.clear();
    tmp_points1.clear();
    for (size_t i = 0; i < status.size(); ++i) {
        if (status[i]) {
            cv::circle(frame0, points0[i], 1, cv::Scalar(0, 255, 0));
            cv::circle(frame0, points1[i], 1, cv::Scalar(0, 0, 255));
            cv::line(frame0, points0[i], points1[i], cv::Scalar(0, 0, 0));
            tmp_points0.push_back(points0[i]);
            tmp_points1.push_back(points1[i]);
        }
    }
    E = cv::findEssentialMat(tmp_points1, tmp_points0, f_, pp_, cv::RANSAC, 0.999, 1.0, mask);
    cv::recoverPose(E, tmp_points1, tmp_points0, R, t, f_, pp_, mask);

    double t1 = std::atan2(R.at<double>(2, 1), R.at<double>(2, 2)) * 180 / M_PI;
    double t2 = std::asin(-R.at<double>(2, 0)) * 180 / M_PI;
    double t3 = std::atan2(R.at<double>(1, 0), R.at<double>(0, 0)) * 180 / M_PI;

    if (abs(t1) < 100 && abs(t2) < 100 && abs(t3) < 100 &&
        t.at<double>(2) > t.at<double>(0) && 
        t.at<double>(2) > t.at<double>(1)) {
		t_ = t_ + R_ * t;
	    R_ = R_ * R;
	}

    std::unique_ptr<VisualizationData> visualization_data(new MonoImageVisualizationData(frame0));

    gray0 = std::move(gray1);
    frame0 = std::move(frame1);
    prev_data_ = std::move(data);
    points0 = std::move(tmp_points1);

    return std::make_tuple(
        std::move(std::unique_ptr<PositionData>(new MonoImagePositionData(R_, t_))),
        std::move(visualization_data));
}
