#pragma once
#include <string>
#include "Constant.h"
#include <cmath>

class clsCheck
{
public:

	static bool CheckPrime(int number)
	{
		if (number == 1)
			return false;
		if (number == 2)
			return true;
		if (number % 2 == 0)
			return false;

		int M = sqrt(number);
		for (int i = 3; i <= M; i += 2)
		{
			if (number % i == 0)
			{
				return false;
			}
		}
		return true;
	}

	static bool CheckEven(int n)
	{
		return n % 2 == 0;
	}

	static bool CheckOdd(int n)
	{
		return n % 2 == 1;
	}

	static bool CheckZero(int number)
	{
		return number == 0;
	}

	static bool CheckMark(float mark, float passMark)
	{
		return mark >= passMark;
	}

	static bool CheckDimension(double dimension)
	{
		return dimension > Constant::MIN_LENGTH && dimension <= Constant::MAX_LENGTH;
	}

	static bool CheckLength(const std::string& Input, short RequiredLength)
	{
		return Input.length() == RequiredLength;
	}

	static bool CheckLeapYear(short Year)
	{
		return (Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0;
	}
};

