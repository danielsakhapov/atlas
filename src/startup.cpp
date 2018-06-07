#include "startup.h"

namespace atlas {

void Startup::Start(int argc, char* argv[])
{
    System sys;
    CommandLineParser parser;
    std::unique_ptr<View> view;
    std::unique_ptr<Model> model;
    std::unique_ptr<Filter> filter;
    std::unique_ptr<Mapper> mapper;

    std::ifstream file("../config/args_table.config");

    if (!file.is_open()) {
        Logger::FatalError({"can not open args table file"});
    }

    std::map<std::string, std::string> args_table;

    std::string str;
    while (std::getline(file, str)) {
        str.erase(
            std::remove_if(str.begin(), str.end(), isspace), 
            str.end());
        auto pos = str.find(":");
        args_table.emplace(
            str.substr(0, pos), 
            str.substr(pos + 1, str.size()));
    }

    parser.SetArgumentsTable(args_table);
    parser.Parse(argc, argv);
    sys.Initialize(parser);
    
    str = sys.GetConfigValue("Mode");
    Logger::Info({"working mode is " + str});
    if (str == "MonoImage") {
        model.reset(new MonoImageModel());
        filter.reset(new MonoImageFilter());
        mapper.reset(new MonoImageMapper());
    }

    if (!model) {
        Logger::FatalError({"Model is not set"});
    }
    if (!filter) {
        Logger::FatalError({"Filter is not set"});
    }
    if (!mapper) {
        Logger::FatalError({"Mapper is not set"});
    } 

    model->Initialize(sys);

    str = sys.GetConfigValue("View");
    Logger::Debug({"initializing View as " + str});
    if (str == "AtlasUI") {
        view.reset(new AtlasUIView());
    }

    if (!view) {
        Logger::FatalError({"View is not set"});
    }

    Controller controller(
        std::move(model), 
        std::move(view), 
        std::move(filter), 
        std::move(mapper));

    controller.MainLoop(argc, argv);
    std::cerr << "Here" << std::endl;
}

} // namespace atlas