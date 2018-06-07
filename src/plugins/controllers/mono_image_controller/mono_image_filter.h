#ifndef MONO_IMAGE_FILTER_H
#define MONO_IMAGE_FILTER_H

#include <tuple>
#include <memory>

#include <opencv2/opencv.hpp>

#include "filter.h"
#include "logger.hpp"

#include "processed_sensor_data.h"
#include "mono_image_calibration_data.h"
#include "mono_image_visualization_data.h"
#include "mono_image_processed_odometry_data.h"

#include "mono_image_odometry_filter.h"

class MonoImageFilter final : public atlas::Filter
{
public:
    MonoImageFilter() = default;
    ~MonoImageFilter() = default;

    virtual void Initialize(
        std::shared_ptr<CalibrationData> calibration_data,
        std::unique_ptr<ProcessedSensorData> sensor_data,
        std::unique_ptr<ProcessedOdometryData> odometry_data) final;
    virtual std::tuple<
                std::unique_ptr<PositionData>,
                std::unique_ptr<VisualizationData>,
                std::unique_ptr<VisualizationData>>
    FilterStep(
        std::unique_ptr<ProcessedSensorData> sensor_data,
        std::unique_ptr<ProcessedOdometryData> odometry_data) final;
};

#endif // MONO_IMAGE_FILTER_H
