#ifndef PROCESSED_ODOMETRY_DATA_H
#define PROCESSED_ODOMETRY_DATA_H

#include <stddef.h>

struct ProcessedOdometryData
{
	ProcessedOdometryData() = default;
	virtual ~ProcessedOdometryData() = default;

	size_t id;
};

#endif // PROCESSED_ODOMETRY_DATA_H
