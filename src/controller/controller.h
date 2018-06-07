#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <thread>

#include "view.h"
#include "model.h"
#include "filter.h"
#include "mapper.h"
#include "system.h"
#include "logger.hpp"
#include "command_line_parser.hpp"

#include "views_list.h"
#include "models_list.h"
#include "controllers_list.h"

#include "calibration_data.h"
#include "visualization_data.h"
#include "processed_sensor_data.h"
#include "processed_odometry_data.h"

namespace atlas {

class Controller
{
public:
    Controller(
        std::unique_ptr<Model> model, 
        std::unique_ptr<View> view,
        std::unique_ptr<Filter> filter,
        std::unique_ptr<Mapper> mapper);
    ~Controller() = default;

    void MainLoop(
        int argc, 
        char* argv[]);

private:
    std::unique_ptr<View> view_;
    std::unique_ptr<Model> model_;
    std::unique_ptr<Filter> filter_;
    std::unique_ptr<Mapper> mapper_;
};

} // namespace atlas

#endif // CONTROLLER_H
