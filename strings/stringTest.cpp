#include <iostream>
#include <assert.h>
#include <cstring>
#include <string>
#include <algorithm> // std::max/min

// from Cracking the coding... task 1.2
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

	// another way (faster? shorter?) would be to
	// use pointer arithmetic instead of array[]
}

// frow Cracking the coding... task 1.3
bool isAnagram(const char *strA, const char *strB)
{
	// one way is to sort strings
	// another is to count character occurence

	const int lenA = strlen(strA);
	const int lenB = strlen(strB);

	if (lenA != lenB)
		return false;

	int occurrence[128] = { 0 };

	for (int i = 0; i < lenA; ++i)
		occurrence[strA[i]]++;

	for (int i = 0; i < lenB; ++i)
		occurrence[strB[i]]--;

	for (int i = 0; i < 128; ++i)
		if (occurrence[i] != 0)
			return false;

	return true;
}

// from Cracking the Coding... task 1.4
// encode ' ' into '%20'
// assume input string has needed place
void encodeSpaces(char *str)
{
	const int len = strlen(str);

	// count ' '
	int spaces = 0;
	for (int i = 0; i < len; ++i)
		if (str[i] == ' ')
			spaces++;
	
	if (spaces > 0)
	{
		const int finalLen = len + spaces * 2;
		int pos = finalLen - 1;
		for (int i = len - 1; i >= 0 && spaces > 0; i--)
		{
			if (str[i] == ' ')
			{
				str[pos] = '0';
				str[pos - 1] = '2';
				str[pos - 2] = '%';
				pos -= 3;
				spaces--;
			}
			else
			{
				str[pos] = str[i];
				--pos;
			}
		}
		str[finalLen] = '\0';
	}
}

int countProbableCompressionLen(const char *original, int originalLen)
{
	// count if we can compress anything:
	int compressedLen = originalLen;
	char prevChar = original[0];
	int groups = 1;
	int groupLen = 1;

	for (int i = 1; i < originalLen; ++i)
	{
		if (prevChar == original[i] && groupLen < 10)
		{			
			++groupLen;
			--compressedLen;
		}
		else
		{
			++groups;
			groupLen = 1;
		}

		prevChar = original[i];
	}

	// each group adds one character (a digit)
	// why '-1' ?
	compressedLen += groups;

	return compressedLen;
}

void compressStringInternal(const char *original, int originalLen, char *output, int compressedLen)
{
	char prevChar = original[0];
	int groups = 1;
	int groupLen = 1;
	char groupLetter = original[0];

	output[0] = original[0];
	int outPos = 1;

	for (int i = 1; i < originalLen; ++i)
	{
		if (prevChar == original[i] && groupLen < 10)
		{
			++groupLen;
		}
		else
		{
			// finish previous group:
			if (groupLen > 2)
				output[outPos++] = '0' + groupLen;
			else
				output[outPos++] = groupLetter;

			groupLen = 1;
			groupLetter = original[i];
			output[outPos++] = groupLetter;
		}

		prevChar = original[i];
	}

	if (groupLen > 2)
		output[outPos++] = '0' + groupLen;
	else
		output[outPos++] = groupLetter;
}

bool compressString(const char *original, char **output, int *outLen)
{
	if (original == NULL || original[0] == '\0' || output == NULL)
	{
		if (output) *output = NULL;
		if (outLen) *outLen = 0;
		return false;
	}

	const int originalLen = strlen(original);

	const int compressedLen = countProbableCompressionLen(original, originalLen);

	if (compressedLen >= originalLen)
	{
		if (output) *output = NULL;
		if (outLen) *outLen = originalLen;
		return false;
	}

	*output = new char[compressedLen + 1];
	(*output)[compressedLen] = '\0';
	*outLen = compressedLen;
	assert(*output);
	compressStringInternal(original, originalLen, *output, compressedLen);

	return true;
}

void internalIntegerToStringReverse(char buffer[16], const unsigned num, unsigned int *len)
{
	unsigned int temp = num;
	int strId = 0;
	while (temp >= 0)
	{
		buffer[strId++] = static_cast<char>(temp % 10) + '0';
		temp /= 10;
		if (temp == 0) break;
	}
	buffer[strId] = '\0';
	*len = strId;
}

void internalMerge(char aStr[16], char bStr[16], int aLen, int bLen, char output[32])
{
	const int commonLen = aLen + bLen;
	int aId = aLen-1;
	int bId = bLen-1;
	for (int i = commonLen - 1; i >= 0; i--)
	{
		if (i % 2 == 0)
			output[i] = (aId >= 0 ? aStr[aId--] : '0');
		else 
			output[i] = (bId >= 0 ? bStr[bId--] : '0');
	}
}

std::string twoNumbersConcat(const unsigned int a, const unsigned int b)
{
	char aStr[16] = { 0 }; // max len of int32, decimal is 10 chars 2,147,483,647
	char bStr[16] = { 0 };
	char output[32] = { 0 };

	unsigned aLen = 0, bLen = 0;
	internalIntegerToStringReverse(aStr, a, &aLen);
	internalIntegerToStringReverse(bStr, b, &bLen);

	internalMerge(aStr, bStr, aLen, bLen, output);

	return std::string(output);
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

	std::cout << isAnagram("hello", "olleh") << std::endl;
	std::cout << isAnagram("ABcdefgh", "abcdefgh") << std::endl;

	char strEncode[8+4] = "ab ab a";
	encodeSpaces(strEncode);
	std::cout << strEncode << std::endl;
	
	char strEncode1[] = "ababa";
	encodeSpaces(strEncode1);
	std::cout << strEncode1 << std::endl;

	char strEncode2[5+8] = "    ";
	encodeSpaces(strEncode2);
	std::cout << strEncode2 << std::endl;

	char *compressed = NULL;
	int outLen = 0;
	if (compressString("abc", &compressed, &outLen))
		std::cout << compressed << std::endl;
	delete[] compressed;

	std::cout << twoNumbersConcat(10, 123) << std::endl;
}
