//example to illustrate the use of heap
#include "heap.h"

class comparator
{
public:
	bool operator () (int k1, int k2)
	{
		return k1 > k2;//comparator for min heap
	}
};

int main(int argc, char const *argv[])
{
	std::cout << "This is example Priority Queue/ Min heap" << std::endl;
	heap<int,comparator> pq;
 
	for(int n : {1,8,5,6,3,4,0,9,7,2})
	{
		pq.push(n);
	}

	while(!pq.empty())
	{
		std::cout << pq.top() << std::endl;
		pq.pop();
	}
	return 0;
}