#pragma once
#include "enum.h"
#include <iostream>

class clsStringCheck
{
public:
	static bool IsVowel(char Character)
	{
		Character = toupper(Character);

		return (
			(Enum::VowelsCharacter)Character == Enum::VowelsCharacter::A ||
			(Enum::VowelsCharacter)Character == Enum::VowelsCharacter::E ||
			(Enum::VowelsCharacter)Character == Enum::VowelsCharacter::I ||
			(Enum::VowelsCharacter)Character == Enum::VowelsCharacter::O ||
			(Enum::VowelsCharacter)Character == Enum::VowelsCharacter::U
			);
	}
};

