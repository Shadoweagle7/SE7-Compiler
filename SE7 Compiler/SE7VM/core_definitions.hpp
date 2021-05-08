#ifndef SE7_CORE_DEFINITIONS
#define SE7_CORE_DEFINITIONS

#include <cstdlib>
#include <cstddef>
#include <concepts>
#include <chrono>
#include <iterator>

#include "platform.hpp"

namespace SE7 {
	namespace core {
		template<class T>
		concept memory_size = std::unsigned_integral<T> && sizeof(T) <= SE7::platform::pointer_size;

		template<class T>
		concept duration_milliseconds = std::unsigned_integral<T> || std::same_as<T, std::chrono::milliseconds>;

		template<class T>
		class value_wrapper {
		private:
			T value;
		public:
			value_wrapper() requires std::default_initializable<T> {}
			value_wrapper(T val) requires std::copy_constructible<T> : value(val) {}

			T get() const requires std::copy_constructible<T> {
				return this->value;
			}

			T &get() {
				return this->value;
			}

			operator T() const requires std::copy_constructible<T> {
				return this->value;
			}

			operator T &() {
				return this->value;
			}
		};

		template<memory_size M>
		using memory_size_t = value_wrapper<M>;

		template<duration_milliseconds D>
		using duration_milliseconds_t = value_wrapper<D>;

		template<class B, class D>
		concept derives_from = std::is_base_of_v<B, D>;

		template<class B, class D>
		concept inherits_from = std::is_base_of_v<B, D>;

		template<class B, class D>
		concept derives_from_or_is_same_as = std::same_as<B, D> || derives_from<B, D>;

		template<class B, class D>
		concept inherits_from_or_is_same_as = std::same_as<B, D> || inherits_from<B, D>;
	}
}

#ifndef MEMORY_SIZE_V
#define MEMORY_SIZE_V size_t
#endif // !MEMORY_SIZE_T

#ifndef DURATION_MILLISECONDS_V
#define DURATION_MILLISECONDS_V size_t
#endif // !DURATION_MILLISECONDS_T

#ifndef MEMORY_SIZE_T
#define MEMORY_SIZE_T SE7::core::memory_size_t<MEMORY_SIZE_V>
#endif // !MEMORY_SIZE_T

#ifndef DURATION_MILLISECONDS_T
#define DURATION_MILLISECONDS_T SE7::core::duration_milliseconds_t<DURATION_MILLISECONDS_V>
#endif // !DURATION_MILLISECONDS_T


#endif
