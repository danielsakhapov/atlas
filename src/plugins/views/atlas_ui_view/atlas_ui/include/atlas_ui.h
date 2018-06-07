#ifndef ATLASUI_H
#define ATLASUI_H

#include <QMainWindow>

namespace atlas_ui {

namespace Ui {
class AtlasUI;
}

class AtlasUI : public QMainWindow
{
    Q_OBJECT
public:
    explicit AtlasUI(
        QWidget* parent = nullptr);
    ~AtlasUI();

    void ShowMap(
        const QImage& img);
    void ShowFrame(
        const QImage& img);
    void ShowLpMatch(
        const QImage& img);
    void resizeEvent(
        QResizeEvent*) override;

private:
    Ui::AtlasUI* ui_;
};

}

#endif
