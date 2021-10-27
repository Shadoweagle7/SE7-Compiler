#ifndef SE7_ERROR
#define SE7_ERROR

#include <string_view>

enum class logging_levels {
	trace = 0,
	debug,
	info,
	warn,
	error,
	fatal,
	off
};

void error(std::string_view message);
void fatal(std::string_view message);
void __debug(std::string_view message);

#ifdef SE7_DEBUG
#define debug __debug
#else
#define debug
#endif // SE7_DEBUG

#endif
