#pragma once
#include <iostream>
#include <string>
#include <limits>

class clsUtils
{
public:

	static void ClearInputBuffer()
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	static void ClearScreen()
	{
		std::system("cls");
	}

	static void Pause(const std::string& Message)
	{
		std::cout << Message;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		system("pause>0");
	}

	static std::string NumberToText(unsigned int Number)
	{
		std::string result;
		if (Number == 0)
			result += "";

		if (Number >= 1 && Number <= 19)
		{
			std::string arr[] = { "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
			result += arr[Number] + " ";
		}

		if (Number >= 20 && Number <= 99)
		{
			std::string arr[] = { "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };
			result += arr[Number / 10 - 2] + " " + NumberToText(Number % 10);
		}

		if (Number >= 20 && Number <= 99)
		{
			std::string arr[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
			result += arr[Number / 10 - 2] + " " + NumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 199)
		{
			result += "one Hundred " + NumberToText(Number % 100);
		}

		if (Number >= 200 && Number <= 999)
		{
			result += NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
		}

		if (Number >= 1000 && Number <= 1999)
		{
			result += "one Thousand " + NumberToText(Number % 1000);
		}

		if (Number >= 2000 && Number <= 999999)
		{
			result += NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
		}

		if (Number >= 1000000 && Number <= 1999999)
		{
			result += "one Million " + NumberToText(Number % 1000000);
		}

		if (Number >= 2000000 && Number <= 999999999)
		{
			result += NumberToText(Number / 100000) + "Million " + NumberToText(Number % 100000);
		}

		if (Number >= 1000000000 && Number <= 1999999999)
		{
			result += "one Billion " + NumberToText(Number % 1000000000);
		}

		if (Number >= 2000000000 && Number <= 999999999999)
		{
			result += NumberToText(Number / 1000000000) + "Billion " + NumberToText(Number % 1000000000);
		}

		if (Number >= 1000000000000 && Number <= 1999999999999)
		{
			result += "one Trillion " + NumberToText(Number % 1000000000000);
		}
		return result;
	}

	static std::string EncryptText(std::string Text, short Key = Constant::ENCRYPT_KEY)
	{
		std::string EncryptedText = Text;

		for (char& C : EncryptedText)
		{
			C += Key;
		}

		return EncryptedText;
	}

	static std::string DecryptText(std::string EncryptedText, short Key = Constant::ENCRYPT_KEY)
	{
		std::string DecryptedText = EncryptedText;

		for (char& C : DecryptedText)
		{
			C -= Key;
		}

		return DecryptedText;
	}
};

