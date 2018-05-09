#include "system.h"

namespace atlas {

void System::Initialize(const CommandLineParser& parser)
{
	std::ifstream file;
	auto dir = parser.GetOptionValue("config_file");
	if (dir.size()) {
		file.open(dir);
	} else {
		file.open("../config/atlas.config");
	}

	if (!file.is_open()) {
		Logger::FatalError({"can not open config file"});
	}

	std::string str;
	while (std::getline(file, str)) {
 		str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
		uint64_t pos = str.find(":");
		configs_.emplace(str.substr(0, pos), str.substr(pos + 1, str.size()));
	}
}



std::string System::GetConfigValue(const std::string& config) const
{
	auto it = configs_.find(config);
	if (it != configs_.end())
		return it->second;
		
	Logger::Error({"config " + config + " is not found"});
	return std::string();
}

} // namespace atlas