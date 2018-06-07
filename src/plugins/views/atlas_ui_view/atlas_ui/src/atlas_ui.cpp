#include "atlas_ui.h"
#include "ui_atlas_ui.h"

namespace atlas_ui {

AtlasUI::AtlasUI(
    QWidget *parent) :
        QMainWindow(parent),
        ui_(new Ui::AtlasUI)
{
    ui_->setupUi(this);
}

AtlasUI::~AtlasUI()
{
    delete ui_;
}

void AtlasUI::resizeEvent(
    QResizeEvent*)
{
    ui_->map->ResizeLayout(QSize(width(), height()));
    ui_->frame->ResizeLayout(QSize(width(), height()));
    ui_->lp_match->ResizeLayout(QSize(width(), height()));
}

void AtlasUI::ShowMap(
    const QImage& img)
{
    ui_->map->ShowImage(img);
}

void AtlasUI::ShowFrame(
    const QImage& img)
{
    ui_->frame->ShowImage(img);
}

void AtlasUI::ShowLpMatch(
    const QImage& img)
{
    ui_->lp_match->ShowImage(img);
}

}
