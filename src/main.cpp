
#include <smart_queue.h>

#include "smart_dynamic_allocator.h"
#include "static_allocator.h"
#include "dynamic_allocator.h"

#include <iostream>
#include <type_traits>

#include <map>

#include <algorithm>
#include <iterator>

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
		AllocatorDynamic<std::pair<const std::size_t, std::size_t>>>;

using smart_queue =
		SmartQueue<std::size_t,
		SmartDynamicAllocator<std::pair<const std::size_t, std::size_t>, 10>>;

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

	SmartQueue<int> smart_queue1;

	for (int i = 1; i <= 10; i++){
		smart_queue1.push(factorial(i));
	}

	smart_queue smart_queue2;

	for (int i = 1; i <= 10; i++){
		smart_queue2.push(factorial(i));
	}

	for(auto it : smart_queue2){
		std::cout << it << std::endl;
	}
	return 0;
}

