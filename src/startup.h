#ifndef STARTUP_H
#define STARTUP_H

#include <map>
#include <memory>
#include <string>
#include <fstream>

#include "logger.hpp"
#include "command_line_parser.hpp"

#include "view.h"
#include "model.h"
#include "controller.h"

#include "filter.h"
#include "mapper.h"

#include "views_list.h"
#include "models_list.h"
#include "controllers_list.h"

namespace atlas {

class Startup
{
public:
    static void Start(
        int argc, 
        char* argv[]);
};

} // namespace atlas

#endif // STARTUP_H
