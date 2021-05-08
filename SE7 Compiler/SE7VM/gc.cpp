#include "gc.hpp"
#include <cstring>
#include <cstdint>

SE7::gc::page SE7::gc::page::dummy(nullptr, nullptr);

SE7::gc::page::page(byte *page_begin, byte *page_end) 
	: page_begin(page_begin), page_end(page_end) {

	if (page_begin == nullptr && page_end == nullptr) {
		return; // Dummy value -> SE7::gc::page::dummy
	}

	std::intptr_t int_begin = reinterpret_cast<std::intptr_t>(page_begin);
	std::intptr_t int_end = reinterpret_cast<std::intptr_t>(page_end);

	if (int_begin >= int_end) {
		// throw error
	}
}

SE7::gc::byte *SE7::gc::page::begin() {
	return this->page_begin;
}

SE7::gc::byte *SE7::gc::page::begin() const {
	return this->page_begin;
}

SE7::gc::byte *SE7::gc::page::end() {
	return this->page_end;
}

SE7::gc::byte *SE7::gc::page::end() const {
	return this->page_end;
}

SE7::gc::page_table::page_table(byte *memory_begin, byte *memory_end)
	: memory_begin(memory_begin), memory_end(memory_end) {

}

SE7::gc::page_iterator SE7::gc::page_table::begin() {
	return this->pages.begin();
}

SE7::gc::const_page_iterator SE7::gc::page_table::begin() const {
	return this->pages.begin();
}

SE7::gc::page_iterator SE7::gc::page_table::end() {
	return this->pages.end();
}

SE7::gc::const_page_iterator SE7::gc::page_table::end() const {
	return this->pages.end();
}

SE7::gc::gc(
	MEMORY_SIZE_T stack_size_in_bytes,
	MEMORY_SIZE_T heap_size_in_bytes,
	DURATION_MILLISECONDS_T maximum_garbage_collection_duration_hint
) : 
	stack(new byte[stack_size_in_bytes]), 
	heap(new byte[heap_size_in_bytes]),
	stack_size_in_bytes(stack_size_in_bytes),
	heap_size_in_bytes(heap_size_in_bytes),
	maximum_garbage_collection_duration(maximum_garbage_collection_duration_hint),
	stack_page_table(this->stack, this->stack + this->stack_size_in_bytes),
	heap_page_table(this->heap, this->heap + this->heap_size_in_bytes) {
	std::memset(this->stack, 0, this->stack_size_in_bytes);
	std::memset(this->heap, 0, this->heap_size_in_bytes);
}

SE7::gc::~gc() {
	delete[] this->heap;
	delete[] this->stack;
}

SE7::mark_and_sweep_gc::mark_and_sweep_gc(
	MEMORY_SIZE_T stack_size_in_bytes,
	MEMORY_SIZE_T heap_size_in_bytes, 
	DURATION_MILLISECONDS_T maximum_garbage_collection_duration_hint
) : gc(stack_size_in_bytes, heap_size_in_bytes, maximum_garbage_collection_duration_hint) {
}

SE7::gc::byte *SE7::mark_and_sweep_gc::allocate(size_t size) {

}

void SE7::mark_and_sweep_gc::request_collection() const {

}

SE7::mark_and_sweep_gc::~mark_and_sweep_gc() {

}
