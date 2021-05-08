#ifndef SE7_GC
#define SE7_GC

#include <core_definitions.hpp>
#include <vector>
#include <functional>

namespace SE7 {
	class gc {
	public:
		using byte = unsigned char;
	protected:
		byte *stack;
		byte *heap;
		MEMORY_SIZE_T stack_size_in_bytes;
		MEMORY_SIZE_T heap_size_in_bytes;

		std::chrono::milliseconds maximum_garbage_collection_duration;
	public:
		class page;

		using page_iterator = std::vector<page>::iterator;
		using const_page_iterator = std::vector<page>::const_iterator;

		class page_table {
		private:
			friend page;

			std::vector<page> pages;
			byte *memory_begin;
			byte *memory_end;
		public:
			page_table(byte *memory_begin, byte *memory_end);

			page_iterator begin();
			const_page_iterator begin() const;
			page_iterator end();
			const_page_iterator end() const;
		};
	protected:
		page_table stack_page_table;
		page_table heap_page_table;
	public:
		class page {
		private:
			byte *page_begin, *page_end;

			page(byte *page_begin, byte *page_end);
		public:
			static page dummy;

			byte *begin();
			byte *begin() const;
			byte *end();
			byte *end() const;
		};

		gc(
			MEMORY_SIZE_T stack_size_in_bytes,
			MEMORY_SIZE_T heap_size_in_bytes,
			DURATION_MILLISECONDS_T maximum_garbage_collection_duration_hint
		);

		virtual byte *allocate(size_t size) = 0;

		virtual void request_collection() const = 0;

		virtual ~gc();
	};

	class mark_and_sweep_gc : public gc {
	private:

	public:
		mark_and_sweep_gc(
			MEMORY_SIZE_T stack_size_in_bytes,
			MEMORY_SIZE_T heap_size_in_bytes,
			DURATION_MILLISECONDS_T maximum_garbage_collection_duration_hint
		);

		virtual byte *allocate(size_t size);

		virtual void request_collection() const;

		virtual ~mark_and_sweep_gc();
	};
}

#endif


