#include "mono_image_model.h"

void MonoImageModel::Initialize(
    const atlas::System& sys)
{
    auto f = sys.GetConfigValue("DataSourceFocal");
    if (f.empty()) {
        f = "1";
        atlas::Logger::Warning({"DataSourceFocal is not set, so using f = " + f + " instead"});
    }
    auto ppx = sys.GetConfigValue("DataSourcePPX");
    if (ppx.empty()) {
        ppx = "1";
        atlas::Logger::Warning({"DataSourcePPX is not set, so using ppx = " + ppx + " instead"});
    }
    auto ppy = sys.GetConfigValue("DataSourcePPY");
    if (ppy.empty()) {
        ppy = "1";
        atlas::Logger::Warning({"DataSourcePPY is not set, so using ppy = " + ppy + " instead"});
    }

    auto realtime = sys.GetConfigValue("DataSourceRealtime");
    if (realtime == "true") {
        auto n_cap = sys.GetConfigValue("DataSourceCap");
        data_source_.reset(
            new MonoImageDataSource(
                std::stoi(n_cap), 
                std::stod(f), 
                cv::Point2d(std::stod(ppx), std::stod(ppy))
            )
        );
    }
    else {
        auto dir = sys.GetConfigValue("DataSourceDir");
        if (dir.empty()) {
            atlas::Logger::FatalError({"data source dir " + dir + " is not found"});
        }
        data_source_.reset(
            new MonoImageDataSource(
                dir,
                std::stod(f), 
                cv::Point2d(std::stod(ppx), std::stod(ppy))
            )
        );
        
    }
    data_source_->Initialize();

    data_processor_.reset(new MonoImageDataProcessor());

    std::thread main_loop_thread(&Model::MainLoop, this, 0, nullptr);
    main_loop_thread.detach();
}
