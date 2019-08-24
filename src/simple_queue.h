#ifndef SIMPLE_QUEUE_H_
#define SIMPLE_QUEUE_H_

#include <bits/c++config.h>
#include <memory>

#include <assert.h>

template<typename Type, typename Allocator = std::allocator<Type>>
class SimpleQueue{
public:
	SimpleQueue():
		Head(nullptr), Tail(nullptr), count_item(0)
	{};
	~SimpleQueue(){
		while(size != 0){
			auto dealloc_ptr = Head;
			Head = Head->Prev;
			allocator.destroy(dealloc_ptr);
			allocator.deallocate(dealloc_ptr,1);
			size--;
		}
	}

public:
	template<typename T> struct Node;
	using node = Node<Type>;
	using node_ptr = Node<Type>*;
	using alloc_type = typename Allocator::template rebind<Node<Type>>::other;

	template<typename T>
	struct Node{
		Node (const T data):
			data(data), Prev(nullptr)
		{};

		const T data;
		Node<Type>* Prev;
	};

	void push(const Type& data){
		auto memory_ptr = allocator.allocate(1);
		allocator.construct(memory_ptr, data);

		node_ptr new_node = memory_ptr;

		if(Head != nullptr){
			Tail->Prev = new_node;
			Tail = new_node;
		} else {
			Head = Tail = new_node;
		}

		count_item++;
	}

	Type pop(){
		if(Head != nullptr){
			Type data = Head->data;

			auto dealloc_ptr = Head;

			Head = Head->Prev;

			allocator.destroy(dealloc_ptr);
			allocator.deallocate(dealloc_ptr,1);

			count_item--;
			return data;
		}
		return 0;
	}

	class iterator
	{
		public:
		iterator(Node<Type>* node) : m_node(node) {}

		iterator() : m_node(nullptr) {}

		iterator& operator++ ()
		{
			if(m_node != nullptr){
				m_node = m_node->Prev;
			}

			return *this;
		}

		Type operator * ()
		{
			if(m_node == nullptr){
				return 0;
			}
			return m_node->data;
		}

		bool operator==(const iterator& rhg) const
		{
			return m_node == rhg.m_node;
		}

		bool operator!=(const iterator& rhg) const
		{
			return m_node != rhg.m_node;
		}

		private:

		Node<Type>* m_node;
	};

	iterator begin()
	{
		return iterator(Head);
	}

	iterator end()
	{
		return  iterator(Tail->Prev);
	}

	std::size_t size(){
		return count_item;
	}

private:
	node_ptr Head;
	node_ptr Tail;
	alloc_type allocator;
	std::size_t count_item;
};


#endif /* SIMPLE_QUEUE_H_ */
