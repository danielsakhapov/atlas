#ifndef SYSTEM_H
#define SYSTEM_H

#include <map>
#include <string>
#include <utility>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <exception>

#include "logger.hpp"
#include "command_line_parser.hpp"

namespace atlas {

class System
{
public:
    System() = default;
    ~System() = default;

    void Initialize(
        const CommandLineParser& parser);
    std::string GetConfigValue(
        const std::string& config) const;

private:
    std::map<std::string, std::string> configs_;
};

}

#endif // SYSTEM_H
