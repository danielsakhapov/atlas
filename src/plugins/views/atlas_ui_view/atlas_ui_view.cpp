#include "atlas_ui_view.h"

void AtlasUIView::Show(std::unique_ptr<VisualizationData> data)
{
	if (atlas_ui_) {
		auto img = static_cast<MonoImageVisualizationData*>(data.get())->frame;
		atlas_ui_->ShowImage(CvMatToQImage(img));
	}
}



void AtlasUIView::MainLoop(int argc, char* argv[])
{
	QApplication a(argc, argv);
	atlas_ui_ = std::make_unique<atlas_ui::AtlasUI>(new atlas_ui::AtlasUI());
	atlas_ui_->show();
	a.exec();
}



inline QImage AtlasUIView::CvMatToQImage(const cv::Mat& mat)
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



inline QPixmap AtlasUIView::CvMatToQPixmap(const cv::Mat& mat)
{
    return QPixmap::fromImage(CvMatToQImage(mat));
}

