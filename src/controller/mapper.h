#ifndef MAPPER_H
#define MAPPER_H

#include <memory>

#include "logger.hpp"

#include "position_data.h"
#include "visualization_data.h"

namespace atlas {

class Mapper
{
public:
    Mapper() = default;
    virtual ~Mapper() = default;

    virtual void Update(
        std::unique_ptr<PositionData> data) = 0;
    virtual std::unique_ptr<VisualizationData> GetData() const = 0;
};

} // namespace atlas

#endif // MAPPER_H
