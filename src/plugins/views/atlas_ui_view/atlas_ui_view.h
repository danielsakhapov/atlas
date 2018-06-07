#ifndef ATLAS_UI_VIEW_H
#define ATLAS_UI_VIEW_H

#include <memory>

#include <QApplication>

#include <opencv2/opencv.hpp>

#include "view.h"
#include "atlas_ui.h"
#include "mono_image_visualization_data.h"

class AtlasUIView final : public atlas::View
{
public:
    AtlasUIView() = default;
    ~AtlasUIView() = default;

    void MainLoop(
        int argc, 
        char* argv[]) final;
    void Show(
        std::unique_ptr<VisualizationData> map,
        std::unique_ptr<VisualizationData> sensor_data,
        std::unique_ptr<VisualizationData> odometry_data) final;
private:
    std::unique_ptr<atlas_ui::AtlasUI> atlas_ui_;

    inline QImage CvMatToQImage(
        cv::Mat&& mat);
    inline QPixmap CvMatToQPixmap(
        cv::Mat&& mat);
};

#endif // ATLAS_UI_VIEW_H
