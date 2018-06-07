#ifndef MONO_IMAGE_ODOMETRY_FILTER_H
#define MONO_IMAGE_ODOMETRY_FILTER_H

#include <tuple>
#include <memory>

#include <opencv2/opencv.hpp>

#include "logger.hpp"
#include "odometry_filter.h"

#include "mono_image_position_data.h"
#include "mono_image_calibration_data.h"
#include "mono_image_visualization_data.h"
#include "mono_image_processed_odometry_data.h"

class MonoImageOdometryFilter final : public atlas::OdometryFilter
{
public:
    MonoImageOdometryFilter() = default;
    ~MonoImageOdometryFilter() = default;

    virtual void Initialize(
        std::shared_ptr<CalibrationData> calibration_data,
        std::unique_ptr<ProcessedOdometryData> odomerty_data) final;
    virtual std::tuple<
                std::unique_ptr<PositionData>,
                std::unique_ptr<VisualizationData>>
    FilterStep(
        std::unique_ptr<ProcessedOdometryData> data) final;

private:
    double f_;
    cv::Mat R_;
    cv::Mat t_;
    cv::Point2d pp_;
    cv::Mat mask, R, t, E;
    std::vector<float> err;
    std::vector<unsigned char> status;
    cv::Mat frame0, frame1, gray0, gray1;
    std::vector<cv::KeyPoint> key_points0;
    std::vector<cv::Point2f> points0, points1;
    std::vector<cv::Point2f> tmp_points0, tmp_points1;
};

#endif // MONO_IMAGE_ODOMETRY_FILTER_H
