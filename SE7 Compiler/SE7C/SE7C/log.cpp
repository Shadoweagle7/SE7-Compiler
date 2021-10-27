#include "log.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

class invalid_logging_level : public std::runtime_error {
public:
	invalid_logging_level(logging_levels level) : 
		std::runtime_error(
			"Invalid logging level " +
			std::to_string(
				static_cast<size_t>(
					level
				)
			)
		) 
	{}
};

constexpr std::string_view levels[] = {
	"TRACE",
	"DEBUG",
	"INFO",
	"WARN",
	"ERROR",
	"FATAL",
	"OFF"
};

void write_to_console(
	logging_levels level, 
	std::string_view message
) {
	size_t level_number = static_cast<size_t>(level);

	if (level_number > sizeof(levels) / sizeof(levels[0])) {
		throw invalid_logging_level(level);
	}

#pragma warning(disable:6385) // We know that level_number is in safe ranges at this point
	std::cout << "[SE7!log" << levels[level_number] << "]: " << message << "\n";
#pragma warning(restore:6385)
}

void error(std::string_view message) {
	write_to_console(logging_levels::error, message);
}

void fatal(std::string_view message) {
	write_to_console(logging_levels::fatal, message);
}

void __debug(std::string_view message) {
#ifdef SE7_DEBUG
#undef debug
	write_to_console(logging_levels::debug, message);
#endif // SE7_DEBUG
}
