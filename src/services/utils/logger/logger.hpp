#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>
#include <exception>

namespace atlas {

struct LoggerInfo
{
	std::string msg;
};

class Logger
{
public:
	static void Info(const LoggerInfo& info)
	{
		std::cout << "[i] " <<  info.msg << "\n";
	}

	static void Debug(const LoggerInfo& info)
	{
		std::cout << "[d] " << info.msg << "\n";
	}

	static void Warning(const LoggerInfo& info)
	{
		std::cerr << "[w] " << info.msg << "\n";
	}

	static void Error(const LoggerInfo& info)
	{
		std::cerr << "[e] " << info.msg << "\n";
	}

	static void FatalError(const LoggerInfo& info)
	{
		std::cerr << "[f] " << info.msg << "\n";
		throw std::runtime_error(info.msg);
	}

};

} // namespace atlas

#endif // LOGGER_H
