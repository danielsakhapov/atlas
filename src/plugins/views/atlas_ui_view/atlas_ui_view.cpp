#include "atlas_ui_view.h"

void AtlasUIView::Show(
    std::unique_ptr<VisualizationData> mapper_data,
    std::unique_ptr<VisualizationData> sensor_data,
    std::unique_ptr<VisualizationData> odometry_data)
{
    if (atlas_ui_) {
        if (mapper_data) {
            auto map = static_cast<MonoImageVisualizationData*>(mapper_data.get())->frame;
            atlas_ui_->ShowMap(
                CvMatToQImage(std::move(map)));
        }
        if (sensor_data) {
            auto lp_match = static_cast<MonoImageVisualizationData*>(sensor_data.get())->frame;
            atlas_ui_->ShowLpMatch(
                CvMatToQImage(std::move(lp_match)));
        }
        if (odometry_data) {
            auto frame = static_cast<MonoImageVisualizationData*>(odometry_data.get())->frame;
            atlas_ui_->ShowFrame(
                std::move(CvMatToQImage(std::move(frame))));
        }
    }
}

void AtlasUIView::MainLoop(
    int argc, 
    char* argv[])
{
    QApplication a(argc, argv);
    atlas_ui_ = std::make_unique<atlas_ui::AtlasUI>(new atlas_ui::AtlasUI());
    atlas_ui_->show();
    a.exec();
}

inline QImage AtlasUIView::CvMatToQImage(
    cv::Mat&& mat)
{
    switch (mat.type()) {
        case CV_8UC4:
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB32);

        case CV_8UC3:
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888).rgbSwapped();

        case CV_8UC1:
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);

    }
    return QImage();
}

inline QPixmap AtlasUIView::CvMatToQPixmap(
    cv::Mat&& mat)
{
    return QPixmap::fromImage(CvMatToQImage(std::move(mat)));
}

