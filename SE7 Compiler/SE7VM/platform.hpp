#ifndef SE7_PLATFORM
#define SE7_PLATFORM

#include <cstdint>
#include <tuple>

#if defined(_WIN32) && !defined(_WIN64)
#define SE7_PLATFORM_OS "windows"
#define SE7_PLATFORM_OS_VERSION "10.0.19402 Build 19402"
#define SE7_PLATFORM_BIT 32
#elif defined(_WIN64)
#define SE7_PLATFORM_OS "windows"
#define SE7_PLATFORM_VERSION "10.0.19402 Build 19402"
#define SE7_PLATFORM_BIT 64
#else

#endif // _WIN32

namespace SE7 {
	namespace platform {
		constexpr const char *const os = SE7_PLATFORM_OS;
		constexpr const char *const os_version = SE7_PLATFORM_OS_VERSION;
		constexpr size_t bit = SE7_PLATFORM_BIT;
		constexpr size_t pointer_size = sizeof(std::intptr_t);
	}
}

#define HAS_CPP20_CONCEPT_AUTO_PARAMETERS 0

#endif
