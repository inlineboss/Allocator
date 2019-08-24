#ifndef SMART_DYNAMIC_ALLOCATOR_H_
#define SMART_DYNAMIC_ALLOCATOR_H_

#include <memory>
#include <optional>

template<typename T, std::size_t SIZE = 10>
class SmartDynamicAllocator{
public:
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;

private:
	using memory_block = uint8_t[];
	using memory_ptr = void*;
	const std::size_t size_memory_block = SIZE * sizeof(value_type);

public:
	std::unique_ptr<memory_block> smart_memory_block;
	std::size_t offset;
public:

	SmartDynamicAllocator():
		offset(0)
	{}

	~SmartDynamicAllocator(){
		offset = 0;
	}

	SmartDynamicAllocator(SmartDynamicAllocator<T>&& alloc_object):
		smart_memory_block(std::move(alloc_object.smart_memory_block)),
		offset(alloc_object.offset)
	{
		alloc_object.offset = 0;
	};

	template <class U>
	struct rebind{
		using other = SmartDynamicAllocator<U, SIZE>;
	};

	pointer allocate(size_type n, [[maybe_unused]] const_pointer hint = 0){

		if(!smart_memory_block){
			smart_memory_block = std::make_unique<memory_block>(sizeof(T) * SIZE);
		}

		if(offset + sizeof(value_type) * n > size_memory_block){
			throw std::bad_alloc();
		}

		memory_ptr mem_p = smart_memory_block.get() + offset;
		offset += n * sizeof(value_type);

		return static_cast <pointer>(mem_p);
	};

	void deallocate(pointer, size_type = 0){
	}

	template< class U, class... Args >
	void construct( U* p, Args&&... args ){
		new(p) U(std::forward<Args>(args)...);
	}

	template< class U >
	void destroy( U*){
	}
};

#endif /* SMART_DYNAMIC_ALLOCATOR_H_ */
