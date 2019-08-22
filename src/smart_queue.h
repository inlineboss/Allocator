#ifndef SMART_STACK_H_
#define SMART_STACK_H_

#include <bits/c++config.h>
#include <memory>


#include <assert.h>

template<typename Type, typename Allocator = std::allocator<Type>>
class SmartQueue{
public:
	template<typename T> struct Node;

	using smart_node = typename Node<Type>::smart_node;
	using node = Node<Type>;

	using alloc_type = typename Allocator::template rebind<Node<Type>>::other;

	template<typename T>
	struct Node{
		struct NodeDeleter
		{
			void operator()(Node<T>* p)
			{
				p->~Node();
				p->allocator->deallocate(p, 1);
			}
		};
		using node = Node<T>;
		using smart_node = std::unique_ptr<node, NodeDeleter>;
		Node (const T& data, alloc_type* allocator):
			data(data), allocator(allocator)
		{};



		smart_node Prev;
		const T data;
		alloc_type* allocator;
	};

	void push(const Type& data){

		auto memory_ptr = allocator.allocate(1);
		allocator.construct(memory_ptr, data, &allocator);

		smart_node new_node(memory_ptr);

		if(!Head){
			Head = std::move(new_node);
			Tail = &Head->Prev;
			return;
		}

		(*Tail) = std::move(new_node);
		Tail = &(*Tail)->Prev;
	}

	Type pop(){
		if(Head){
			Type data = Head->data;
			Head = std::move(Head->Prev);
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
			if(m_node == nullptr){
				return *this;
			} else {
				m_node = m_node->Prev.get();
				return *this;
			}


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
		return iterator(Head.get());
	}

	iterator end()
	{
		return  iterator(Tail->get());
	}
private:
	smart_node Head;
	smart_node* Tail;
	alloc_type allocator;
};


#endif /* SMART_STACK_H_ */
