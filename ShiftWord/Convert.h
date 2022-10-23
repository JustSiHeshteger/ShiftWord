#pragma once
#include <ctype.h>
class Convert
{
public:
	static bool CheckOnNumber(char* inputString)
	{
		bool dot = false;
		int index = 0, length = Convert::GetLength(inputString);

		if (inputString[index] == '-')
			index++;

		while (index != length)
		{
			if (dot)
			{
				if (inputString[index] != 0x30)
					return false;
			}
			else if (inputString[index] == '.' || inputString[index] == ',')
			{
				if (!dot)
					dot = true;
				else
					return false;

				if (index == length - 1)
					return false;
			}
			else if (!isdigit(inputString[index]))
			{
				return false;
			}
			
			index++;
		}

		return true;
	}

	static int ToInt32(char* inputString)
	{
		bool isNegative = false;
		int index = 0, number = 0, length = Convert::GetLength(inputString);

		if (inputString[index] == '-')
		{
			isNegative = true;
			index++;
		}

		while (index < length)
		{
			number += (inputString[index] & 0x0F);
			number *= 10;
			index++;
		}

		number /= 10;

		if (isNegative)
			number = -number;

		return number;
	}

	static int GetLength(char* inputString)
	{
		int index = 0;

		while (inputString[index] != 0x00)
		{
			index++;
		}

		return index;
	}

	static int GetLength(wchar_t* inputString)
	{
		int index = 0;

		while (inputString[index] != 0x00)
		{
			index++;
		}

		return index;
	}
};

