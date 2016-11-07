/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////	stl style templated heap implementation	/////
/////	it supports normal/stl heap operations	/////
/////	and an update value/priority operations	/////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

#ifndef P_HEAP_H
#define P_HEAP_H

#include <iostream>
#include <vector>
#include <algorithm>

// template heap object T
// Compare is comparision class
template< typename T, typename Compare>
class heap
{

private:
	//container to hold heap objects
	std::vector< T > container;

protected:
	//few helper functions
	size_t parent(size_t i);
	size_t left_child(size_t i);
	size_t right_child(size_t i);
	void shift_up(size_t index);
	void shift_down(size_t index);

public:
	//stl operations
	heap();
	heap(T * start, T * end);
	~heap(){}
	bool empty();
	size_t size();
	void push(T to_push);
	T top();
	void pop();
	//update element operation
	//takes the position where to update
	//and the element with which to update
	void update(size_t index, T with);
};

template< typename T, typename Compare>
heap< T, Compare>::heap()
{
	//do nothing
}

template< typename T, typename Compare>
heap< T, Compare>::heap(T * start, T * end)
{
	for (T * i = start; i < end; ++i)
	{
		container.push_back(*i);
	}
	std::make_heap(container.begin(),container.end(),Compare());
}

template< typename T, typename Compare>
bool heap< T, Compare>::empty()
{
	return (container.size() == 0);
}

template< typename T, typename Compare>
size_t heap< T, Compare>::size()
{
	return container.size();
}

template< typename T, typename Compare>
size_t heap< T, Compare>::parent(size_t i)
{
	return ((i-1) >> 1);
}

template< typename T, typename Compare>
size_t heap< T, Compare>::left_child(size_t i)
{
	return ((i) << 1) + 1;
}

template< typename T, typename Compare>
size_t heap< T, Compare>::right_child(size_t i)
{
	return ((i+1) << 1);
}

template< typename T, typename Compare>
void heap< T, Compare>::shift_up(size_t index)
{
	while(index > 0 && Compare()(container[parent(index)],container[index]))
	{
		std::swap(container[index],container[parent(index)]);
		index = parent(index);
	}
}

template< typename T, typename Compare>
void heap< T, Compare>::shift_down(size_t index)
{
	while((left_child(index) < container.size() && Compare()(container[index],container[left_child(index)])) || 
			(right_child(index) < container.size() && Compare()(container[index],container[right_child(index)])))
	{
		if(right_child(index) < container.size())
		{
			if(Compare()(container[right_child(index)],container[left_child(index)]))
			{
				std::swap(container[index],container[left_child(index)]);
				index = left_child(index);
			}
			else
			{
				std::swap(container[index],container[right_child(index)]);
				index = right_child(index);
			}
		}
		else
		{
			std::swap(container[index],container[left_child(index)]);
			index = left_child(index);
		}
	}
}

template< typename T, typename Compare>
void heap< T, Compare>::push(T to_push)
{
	container.push_back(to_push);
	shift_up(container.size()-1);
}

template< typename T, typename Compare>
T heap< T, Compare>::top()
{
	return container[0];
}

template< typename T, typename Compare>
void heap< T, Compare>::pop()
{
	container[0] = container[container.size()-1];
	container.pop_back();
	shift_down(0);
}

template< typename T, typename Compare>
void heap< T, Compare>::update(size_t index, T with)
{
	if(Compare()(container[index],with))
	{
		container[index] = with;
		shift_up(index);
	}
	else
	{
		container[index] = with;
		shift_down(index);
	}
}

#endif