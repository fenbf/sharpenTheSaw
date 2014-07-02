#include <iostream>

void reverseCString(char *str)
{
	// find len:
	unsigned int len = 0;
	char *s = str;
	while (*s != '\0')
	{
		++len;
		++s;
	}

	for (unsigned int i = 0; i < len / 2; ++i)
	{
		char t = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = t;
	}
}

void stringTest()
{
	// !!does not work!!, runtime error!
	// cannot modify read only memory wirh strings...
	char *strPtr = "Hexlo World!";
	// strPtr[2] = 'l'; << runtime err

	// works fine: this is only an array initialization
	char strArr[] = "Hexlo World!";
	strArr[2] = 'l';

	std::cout << "sizeof(strPtr) = " << sizeof(strPtr) << std::endl;
	std::cout << "sizeof(strArr) = " << sizeof(strArr) << std::endl;
}

int main()
{
	stringTest();

	char test[] = "abcdefghij";
	std::cout << test << std::endl;
	reverseCString(test);
	std::cout << test << std::endl;
}