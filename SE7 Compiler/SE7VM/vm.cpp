#include <vm.hpp>

#include <utility>

SE7::vm::vm(
	std::unique_ptr<gc> &&garbage_collector
) : 
	garbage_collector(
		std::move(garbage_collector)
	) {
}
