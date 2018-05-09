#ifndef VISUALIZATION_DATA_H
#define VISUALIZATION_DATA_H

#include <stddef.h>

struct VisualizationData
{
	VisualizationData() = default;
	virtual ~VisualizationData() = default;

	size_t id;
};

#endif // VISUALIZATION_DATA_H
