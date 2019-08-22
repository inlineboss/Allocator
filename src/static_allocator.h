#ifndef STATIC_ALLOCATOR_H_
#define STATIC_ALLOCATOR_H_

#include <type_traits>
#include <stdint.h>
#include <bits/move.h>
#include <new>

template<typename T, std::size_t SIZE = 10>
class StaticAllocator{
public:
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;

private:
	using memory_block = uint8_t*;
	using memory_ptr = void*;
	const std::size_t size_memory_block = SIZE * sizeof(value_type);

public:
	memory_block ptr;
	std::size_t offset;
public:
	StaticAllocator():
		ptr{nullptr},
		offset(0)
	{}

	~StaticAllocator(){
		offset = 0;
	}

	StaticAllocator(const StaticAllocator<T>& alloc_object):
		ptr{nullptr},
		offset(0)
	{};

	template <class U>
	struct rebind{
		using other = StaticAllocator<U, SIZE>;
	};

	template <std::size_t COUNT>
	struct allocate_memory_block{
		uint8_t block[COUNT];
	};
	pointer allocate(size_type n, [[maybe_unused]] const_pointer hint = 0){

		if(offset == 0){
			static allocate_memory_block<sizeof(value_type) * SIZE> memory;
			ptr = memory.block;
		}

		if(offset + sizeof(value_type) * n > size_memory_block){
			throw std::bad_alloc();
		}

		memory_ptr mem_p = ptr + offset;
		offset += n * sizeof(value_type);

		return static_cast <pointer>(mem_p);
	};

	void deallocate(pointer p, size_type n){
	}

	template< class U, class... Args >
	void construct( U* p, Args&&... args ){
		new(p) U(std::forward<Args>(args)...);
	}

	template< class U >
	void destroy( U* p ){
	}
};


#endif /* STATIC_ALLOCATOR_H_ */
