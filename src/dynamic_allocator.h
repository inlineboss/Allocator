#ifndef DYNAMIC_ALLOCATOR_H_
#define DYNAMIC_ALLOCATOR_H_

#include <memory>
#include <cstddef>
#include <cstdlib>

template<typename T>
class DynamicAllocator{
public:
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;

	template<typename U>
	DynamicAllocator(const DynamicAllocator<U>&)
	{}

	DynamicAllocator() = default;
	~DynamicAllocator() = default;

	template <class U>
	struct rebind{
		using other = DynamicAllocator<U>;
	};

	pointer allocate(size_type n, const_pointer hint = 0){
		auto ptr = std::malloc(sizeof(T) * n);

		if(ptr == nullptr){
			throw std::bad_alloc();
		}

		return reinterpret_cast <T*>(ptr);
	};

	void deallocate(pointer p, size_type n){
		std::free(p);
	}

	template< class U, class... Args >
	void construct( U* p, Args&&... args ){
		::new(p) U(std::forward<Args>(args)...);
	}

	template< class U >
	void destroy( U* p ){
		p->~U();
	}
};



#endif /* DYNAMIC_ALLOCATOR_H_ */
