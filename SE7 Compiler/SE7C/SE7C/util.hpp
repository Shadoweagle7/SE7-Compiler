#ifndef SE7_UTIL
#define SE7_UTIL
#include <concepts>

template<std::unsigned_integral UI>
constexpr UI make_bit(UI left_shift) {
	return 1 << left_shift;
}

template<std::unsigned_integral UI>
constexpr bool has_bit(UI num, UI bit) {
	return num & bit;
}

#endif
