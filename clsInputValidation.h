#pragma once
#include <string>

class clsInputValidation
{
public:
	static bool IsDigitOnly(const std::string& Input)
	{
		for (char c : Input)
		{
			if (!isdigit(c))
				return false;
		}
		return true;
	}

	static bool IsNumberInRange(int Number, int MinNumber, int MaxNumber)
	{
		if (Number != static_cast<int>(Number))
			return false;

		return Number >= MinNumber && Number <= MaxNumber;
	}

	static bool IsNumberInRange(float Number, float MinNumber, float MaxNumber)
	{
		if (Number != static_cast<float>(Number))
			return false;

		return Number >= MinNumber && Number <= MaxNumber;
	}

	static bool IsValidPinCodet(const std::string& Str)
	{
		if (Str.length() != 4)
		{
			return false;
		}

		if (!IsDigitOnly(Str))
		{
			return false;
		}

		return true;
	}

};

