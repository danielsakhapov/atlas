#ifndef MONO_IMAGE_MODEL_H
#define MONO_IMAGE_MODEL_H

#include <mutex>
#include <queue>
#include <memory>
#include <string>
#include <thread>

#include "model.h"
#include "system.h"
#include "logger.hpp"

#include "mono_image_data_source.h"
#include "mono_image_data_processor.h"
#include "mono_image_calibration_data.h"
#include "mono_image_raw_odometry_data.h"

class MonoImageModel final : public atlas::Model
{
public:
    MonoImageModel() = default;
    ~MonoImageModel() = default;

    void Initialize(
        const atlas::System& sys) final;

private:
    std::mutex odometry_data_mutex_;
    std::queue<ProcessedOdometryData> odometry_data_queue_;
    
    std::shared_ptr<CalibrationData> calibration_data_;
};

#endif // MONO_IMAGE_MODEL_H
