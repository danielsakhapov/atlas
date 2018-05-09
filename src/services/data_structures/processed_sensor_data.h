#ifndef PROCESSED_SENSOR_DATA_H
#define PROCESSED_SENSOR_DATA_H

#include <stddef.h>

struct ProcessedSensorData
{
	ProcessedSensorData() = default;
	virtual ~ProcessedSensorData() = default;

	size_t id;
};

#endif // PROCESSED_SENSOR_DATA_H
