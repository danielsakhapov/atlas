#ifndef RAW_ODOMETRY_DATA_H
#define RAW_ODOMETRY_DATA_H

#include <stddef.h>

struct RawOdometryData
{
	RawOdometryData() = default;
	virtual ~RawOdometryData() = default;

	size_t id;
};

#endif // RAW_ODOMETRY_DATA_H
