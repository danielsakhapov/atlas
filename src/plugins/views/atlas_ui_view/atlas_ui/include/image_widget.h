#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <mutex>

#include <QWidget>
#include <QPainter>

namespace atlas_ui {

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(
        QWidget* parent = nullptr);

    void ShowImage(
        const QImage& img);
    void ResizeLayout(
        const QSize& size);

private:
    int window_width_;
    int window_height_;

    std::mutex data_mutex_;

    QImage image_;
    QPainter painter_;

    void paintEvent(QPaintEvent*) override;
};

}

#endif
