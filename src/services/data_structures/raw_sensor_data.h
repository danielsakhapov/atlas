#ifndef RAW_SENSOR_DATA_H
#define RAW_SENSOR_DATA_H

#include <stddef.h>

struct RawSensorData
{
	RawSensorData() = default;
	virtual ~RawSensorData() = default;

	size_t id;
};

#endif // RAW_SENSOR_DATA_H
