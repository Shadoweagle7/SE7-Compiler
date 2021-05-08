#ifndef SE7_VM
#define SE7_VM

#include <memory>
#include <core_definitions.hpp>
#include <gc.hpp>

namespace SE7 {
	class vm {
	private:
		const std::unique_ptr<gc> garbage_collector;
	public:
		vm(
			std::unique_ptr<gc> &&garbage_collector
		);
	};
}

#endif
