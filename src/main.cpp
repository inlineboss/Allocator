#include <iostream>
#include <type_traits>
#include <map>
#include <algorithm>
#include <iterator>

#include "smart_dynamic_allocator.h"
#include "static_allocator.h"
#include "dynamic_allocator.h"

#include "simple_queue.h"

using smart_dynamic_map =
		std::map<std::size_t, std::size_t,
		std::less<std::size_t>,
		SmartDynamicAllocator<std::pair<const std::size_t, std::size_t>, 10>>;

using static_map =
		std::map<std::size_t, std::size_t,
		std::less<std::size_t>,
		StaticAllocator<std::pair<const std::size_t, std::size_t>, 10>>;

using dynamic_map =
		std::map<std::size_t, std::size_t,
		std::less<std::size_t>,
		DynamicAllocator<std::pair<const std::size_t, std::size_t>>>;

using simple_queue =
		SimpleQueue<std::size_t,
		SmartDynamicAllocator<std::size_t, 10>>;

constexpr std::size_t factorial (std::size_t a){
	return a ? a * factorial(a - 1 ) : 1;
}

template <typename Type1, typename Type2>
std::ostream& operator<< (std::ostream &out, const std::pair<Type1, Type2> &object)
{
    // Поскольку operator<< является другом класса Point, то мы имеем прямой доступ к членам Point
	out << object.first << "\t" << object.second;

    return out;
}

auto make_pair_indx_factor = [i = 0] () mutable
{
   return ++i, std::make_pair(i,factorial(i));
};

#define MSG(X) std::cout << X << std::endl

int main()
{

	std::map<std::size_t, std::size_t> standart_map;

	std::generate_n(
			std::inserter(standart_map, std::begin(standart_map)),
			10,
			make_pair_indx_factor
	);

	for(auto it : standart_map){
		std::cout << it << std::endl;
	}

	smart_dynamic_map map2;

	std::generate_n(
				std::inserter(map2, std::begin(map2)),
				10,
				make_pair_indx_factor
	);

	for(auto it : map2){
		std::cout << it << std::endl;
	}

	SimpleQueue<int> simple_queue1;

	for (int i = 1; i <= 10; i++){
		simple_queue1.push(factorial(i));
	}

	simple_queue queue;

	for (int i = 1; i <= 10; i++){
		queue.push(factorial(i));
	}

	for(auto it : queue){
		std::cout << it << std::endl;
	}
	return 0;
}

