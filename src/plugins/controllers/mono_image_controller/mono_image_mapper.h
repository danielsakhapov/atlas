#ifndef MONO_IMAGE_MAPPER_H
#define MONO_IMAGE_MAPPER_H

#include <memory>

#include <opencv2/opencv.hpp>

#include "mapper.h"
#include "logger.hpp"

#include "position_data.h"
#include "visualization_data.h"

#include "mono_image_position_data.h"
#include "mono_image_visualization_data.h"

class MonoImageMapper final : public atlas::Mapper
{
public:
    MonoImageMapper();
    ~MonoImageMapper() = default;

    virtual void Update(
        std::unique_ptr<PositionData> data) final;
    virtual std::unique_ptr<VisualizationData> GetData() const final;

private:
    const double dx_ = 1500; 
    const double dy_ = 200;

    std::unique_ptr<PositionData> data_;
    std::unique_ptr<MonoImageVisualizationData> map_;
};

#endif // MONO_IMAGE_MAPPER_H
