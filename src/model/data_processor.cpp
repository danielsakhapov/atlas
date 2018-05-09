#include "data_processor.h"

namespace atlas
{

void DataProcessor::SetCalibrationData(std::shared_ptr<CalibrationData> data)
{
	if (data) {
		calibration_data_ = data;
	}
	else {
		atlas::Logger::FatalError({"calibration data is empty while calling MonoImageDataProcessor::SetCalibrationData"});
	}
}

} // namespace atlas
