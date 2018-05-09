#ifndef POSITION_DATA_H
#define POSITION_DATA_H

#include <stddef.h>

struct PositionData
{
	PositionData() = default;
	virtual ~PositionData() = default;

	size_t id;
};

#endif // POSITION_DATA_H
