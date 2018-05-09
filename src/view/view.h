#ifndef VIEW_H
#define VIEW_H

#include <memory>

#include <opencv2/opencv.hpp>

#include "visualization_data.h"

namespace atlas {

class View
{
public:
	virtual ~View() = default;

	virtual void MainLoop(int argc, char* argv[]) = 0;
	virtual void Show(std::unique_ptr<VisualizationData> data) = 0;
};

} // namespace atlas

#endif // VIEW_H
