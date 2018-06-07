#include "mono_image_mapper.h"

MonoImageMapper::MonoImageMapper() :
    map_(new MonoImageVisualizationData(cv::Mat(3000, 3000, CV_8UC3)))
{}

void MonoImageMapper::Update(
    std::unique_ptr<PositionData> data)
{
    if (data) {
        cv::Mat R = static_cast<MonoImagePositionData*>(data.get())->R;
        cv::Mat t = static_cast<MonoImagePositionData*>(data.get())->t;
        cv::circle(map_->frame, cv::Point2f(t.at<double>(0) + dx_, t.at<double>(2) + dy_), 2, cv::Scalar(255, 255, 255), 2);

        data_ = std::move(data);
    }
    else {
        atlas::Logger::Warning({"position data empty while calling MonoImageMapper::Update"});
    }
}

std::unique_ptr<VisualizationData> MonoImageMapper::GetData() const
{
    return std::unique_ptr<VisualizationData>(new MonoImageVisualizationData(map_->frame));
}
