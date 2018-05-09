#ifndef COMMAND_LINE_PARSER_H
#define COMMAND_LINE_PARSER_H

#include <map>
#include <string>
#include <cstdint>
#include <utility>
#include <iostream>

#include "logger.hpp"

namespace atlas {

class CommandLineParser
{
public:
	CommandLineParser() = default;
	~CommandLineParser() = default;

	void SetArgumentsTable(const std::map<std::string, std::string>& args_table)
	{
		args_table_ = args_table;
	}

	void Parse(int argc, char* argv[])
	{
		for (int i = 1; i < argc; ++i) {
			auto arg_size = GetArgumentSize(argv[i]);
			if (arg_size == 1) {
				opts_table_.emplace(argv[i], "true");
			}
			else if (arg_size > 1) {
				if (CheckArgumentValueType(argv[i], argv[i + 1])) {
					opts_table_.emplace(argv[i], argv[i + 1]);
					++i;
				}
				else {
					exit(-1);
				}
			}
			else {
				Logger::FatalError({"invalid agrument name " + std::string(argv[i])});
			}
		}

	}

	std::string GetOptionValue(const std::string& opt) const
	{
		auto it = opts_table_.find('-' + opt);
		if (it != opts_table_.end()) {
			return it->second;
		}

		Logger::Warning({"option " + opt + " is not found"});
		return std::string();
	}

private:
	std::map<std::string, std::string> args_table_;
	std::map<std::string, std::string> opts_table_;

	uint8_t GetArgumentSize(std::string arg)
	{
		arg = arg.substr(1);
		if (args_table_.find(arg) != args_table_.end()) {
			if (args_table_[arg] == "int")
				return 2;
			if (args_table_[arg] == "bool")
				return 2;
			if (args_table_[arg] == "none")
				return 1;
			if (args_table_[arg] == "string")
				return 2;
		}

		return 0;
	}

	bool CheckArgumentValueType(const std::string& arg, const std::string& val_type)
	{
		auto value_type = args_table_[arg];
		// TODO: write checking
		if (true) {
			return true;
		}
		else {
			Logger::FatalError({"invalid type for argument " + arg + "! Expected " + value_type + ". Found " + val_type});
			return false;
		}
	}

};

}

#endif // COMMAND_LINE_PARSER_H
