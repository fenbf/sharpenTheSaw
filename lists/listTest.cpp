#include <iostream>

#include "list.h"

int main()
{
	List<int> list;

	list.add(0);
	list.add(1);
	list.add(2);

	list.iterate([](int &v){
		std::cout << v << ", ";
	});
}