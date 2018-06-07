#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <string>
#include <thread>

#include "system.h"
#include "logger.hpp"
#include "data_source.h"
#include "data_storage.h"
#include "data_processor.h"

namespace atlas {

class Model
{
public:
    Model() = default;
    virtual ~Model() = default;

    void MainLoop(
        int argc, 
        char* argv[]);
    virtual void Initialize(
        const System& sys) = 0;

    bool IsSensorDataLeft() const;
    bool IsOdometryDataLeft() const;
    bool IsCalibrationDataEmpty() const;

    virtual std::unique_ptr<ProcessedSensorData> GetSensorData();
    virtual std::shared_ptr<CalibrationData> GetCalibrationData();
    virtual std::unique_ptr<ProcessedOdometryData> GetOdometryData();

protected:
    DataStorage data_storage_;
    std::unique_ptr<DataSource> data_source_;
    std::unique_ptr<DataProcessor> data_processor_;
};

} // namespace atlas

#endif // MODEL_H
