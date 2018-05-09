#include "atlas_ui.h"
#include "ui_atlas_ui.h"

namespace atlas_ui {

AtlasUI::AtlasUI(QWidget *parent) :
	QMainWindow(parent),
	ui_(new Ui::AtlasUI)
{
	ui_->setupUi(this);
}



AtlasUI::~AtlasUI()
{
	delete ui_;
}



void AtlasUI::resizeEvent(QResizeEvent*)
{
	ui_->imageWidget->ResizeLayout(QSize(width(), height()));
}



void AtlasUI::ShowImage(const QImage& img)
{
	ui_->imageWidget->ShowImage(img);
}

}
