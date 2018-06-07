#include "data_processor.h"

namespace atlas
{

void DataProcessor::SetCalibrationData(
    std::shared_ptr<CalibrationData> data)
{
    if (!data) {
        atlas::Logger::Warning({"calibration data is nullptr while calling DataProcessor::SetCalibrationData"});
    }

    calibration_data_ = data;
}

} // namespace atlas
