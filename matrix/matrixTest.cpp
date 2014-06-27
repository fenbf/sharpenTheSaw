#include <iostream>

void printSpiralRek(int *array, int width, int height, int level, std::ostream &os)
{	
	const int left = level;
	const int right = width - level;
	const int top = level;
	const int bottom = height - level;

	if (left > right && top > bottom)
		return;
	
	// top: left to right
	for (int x = left; x < right; ++x)
		os << array[width*top + x] << ", ";

	// right: top to bottom
	for (int y = top+1; y < bottom; ++y)
		os << array[width*y + right-1] << ", ";

	// bottom: right to left
	for (int x = right-2; x >= left && (bottom-1) > top; --x)
		os << array[width*(bottom-1) + x] << ", ";

	// right: bottom to top
	for (int y = bottom-2; y >= top+1; --y)
		os << array[width*y + + left] << ", ";

	printSpiralRek(array, width, height, level + 1, os);
}

void printSpiral(int *array, int width, int height, std::ostream &os)
{
	printSpiralRek(array, width, height, 0, os);
	os << std::endl;
}

int main()
{
	int arr[] = { 0, 1, 2, 3,
		          4, 5, 6, 7,
		          8, 9, 10, 11,
	              12, 13, 14, 15};

	printSpiral(arr, 4, 4, std::cout);

	int arr2[] = { 00, 01, 02, 03, 05,
	               06, 07, 8,  9, 10,
	               11, 12, 13, 14, 15,
	               16, 17, 18, 19, 20,
	               21, 22, 23, 24, 25 };

	printSpiral(arr2, 5, 5, std::cout);

	return 0;
}
