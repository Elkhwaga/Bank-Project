#pragma once
#include "Enum.h"
#include "clsCheck.h"

class clsEnums
{
public:
	static Enum::PrimeOrNot IsPrimeOrNot(int Number)
	{
		return (clsCheck::CheckPrime(Number)) ? Enum::PrimeOrNot::PRIME : Enum::PrimeOrNot::NOT_PRIME;
	}

	static Enum::OddOrEven GetNumberType(int Number)
	{
		return (Number % 2 == 0) ? Enum::OddOrEven::EVEN : Enum::OddOrEven::ODD;
	}

	static Enum::ChoiceStatus IsContinue(char Choice)
	{
		return (Choice == 'Y' || Choice == 'y') ? Enum::ChoiceStatus::YES : Enum::ChoiceStatus::NO;
	}

	static Enum::Status CheckStatus(float Mark, float PassMark)
	{
		return (clsCheck::CheckMark(Mark, PassMark)) ? Enum::Status::PASS : Enum::Status::FAIL;
	}

	static Enum::PerfectOrNot IsPerfectNumber(int Number)
	{
		int Sum = 0;
		for (int i = 1; i < Number; i++)
		{
			if (Number % i == 0)
				Sum += i;
		}
		return (Number == Sum) ? Enum::PerfectOrNot::PERFECT : Enum::PerfectOrNot::NOT_PERFECT;
	}

	static Enum::PositiveOrNegative GetNumberTypeNegativeOrPositive(int Number)
	{
		return (Number > 0) ? Enum::PositiveOrNegative::POSITIVE : Enum::PositiveOrNegative::NEGATIVE;
	}

	static Enum::CharacterCase GetCharacterCase(char Character)
	{
		return isupper(Character) ? Enum::CharacterCase::CAPITAL : Enum::CharacterCase::SMALL;
	}
};

