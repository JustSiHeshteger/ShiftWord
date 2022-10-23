#include <iostream>
#include <fstream>
#include "Convert.h"

const int _SIZE = 256;

void SetShift(char* word, int wordLength, int shift) 
{
	if (shift > wordLength)
		shift = shift % wordLength;

	for (int i = 0; i < wordLength; i++)
	{
		if (i + shift >= wordLength)
		{
			if (i >= shift)
				std::cout << word[shift + i - wordLength];
			else
				std::cout << word[abs(wordLength - i - shift)];
		}
		else 
		{
			std::cout << word[(shift + i)];
		}
	}
}

void FindWords(char* inputString, int shift)
{
	int allStringLength = Convert::GetLength(inputString) + 1, index = 0, currentWordLength = 0;
	char* buffer = new char[allStringLength];

	while (index < allStringLength)
	{
		if (inputString[index] == ' ' || allStringLength == index + 1)
		{
			if (currentWordLength > 0)
				SetShift(buffer, currentWordLength, shift);

			std::cout << inputString[index];

			currentWordLength = 0;
		}
		else
		{
			buffer[currentWordLength] = inputString[index];
			currentWordLength++;
		}

		index++;
	}
}

bool CheckAddon(char* con)
{
	const int border = 4;
	int index = border, length = Convert::GetLength(con);
	char addon[border];
	const char txt[border] = { '.', 't', 'x', 't'};

	while (index != 0)
	{
		addon[index - 1] = con[length - 1];
		index--;
		length--;
	}

	for (int i = 0; i < border; i++)
	{
		if (addon[i] != txt[i])
			return false;
	}

	return true;
}

bool CheckOnFileExist(char* filePath)
{
	std::ifstream file(filePath);

	try {
		file.seekg(0, std::ios_base::end);
		size_t fSize = file.tellg();
		file.seekg(0);
		char* text;
		text = new char[fSize];
	}
	catch (std::exception ex)
	{
		std::cout << "Не удалось открыть файл." << std::endl;
		file.close();
		return false;
	}

	if (!CheckAddon(filePath))
	{
		std::cout << "Неверное расширение файла." << std::endl;
		file.close();
		return false;	
	}

	if (!file.good())
	{
		std::cout << "Такого файла не существует. Попробуйте еще раз!" << std::endl;
		file.close();
		return false;
	}

	file.close();
	return true;
}

char* GetInputString(const char* message = "")
{
	std::cout << message;

	char* inputString = new char[_SIZE];
	std::cin.getline(inputString, _SIZE);

	int length = Convert::GetLength(inputString);

	char* outputString = new char[length + 1];
	strcpy_s(outputString, length + 1, inputString);
	delete[] inputString;

	return outputString;
}

bool GetDataFile(char* fileName, int shift)
{
	std::ifstream fileStream;
	fileStream.imbue(std::locale(".1251"));

	char inputString[_SIZE];

	try 
	{
		fileStream.open(fileName);

		while (!fileStream.eof())
		{
			fileStream.getline(inputString, _SIZE);
			FindWords(inputString, shift);
			std::wcout << std::endl;
		}

		fileStream.close();
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
		std::cout << "Не удалось прочитать файл. Попробуйте еще раз!" << std::endl;
		return false;
	}

	return true;
}

char* GetPath() 
{
	const char* message = "Введите путь к файлу с указанием расширения (*.txt): ";

	char* filePath = GetInputString(message);

	while (!CheckOnFileExist(filePath))
	{
		filePath = GetInputString(message);
	}

	return filePath;
}

int GetShift()
{
	const char* message = "Введите сдвиг слова (ЦЕЛОЕ, НЕОТРИЦАТЕЛЬНОЕ число; НЕ БОЛЛЕ ЧЕМ (2 147 483 647) ): ";

	char* numberString = GetInputString(message);

	while (true)
	{
		if (!Convert::CheckOnNumber(numberString))
		{
			std::cout << "Введено некорректное значение. Попробуйте еще раз!" << std::endl;
			numberString = GetInputString(message);
			continue;
		}
		else if (Convert::ToInt32(numberString) < 0)
		{
			std::cout << "Введено некорректное значение. Попробуйте еще раз!" << std::endl;
			numberString = GetInputString(message); 
			continue;
		}
		else 
		{
			return Convert::ToInt32(numberString);
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");

	GetDataFile(GetPath(), GetShift());

	system("pause");

	return 0;
}