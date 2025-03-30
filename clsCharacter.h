#pragma once
#include <iostream>

class clsCharacter
{
protected:
	char _Character;

public:
	void SetCharacter(char Character)
	{
		this->_Character = Character;
	}

	char GetCharacter() const
	{
		return this->_Character;
	}

	static char InvertLetterCase(char Character)
	{
		return isupper(Character) ? tolower(Character) : toupper(Character);
	}

	char InvertLetterCase()
	{
		return this->InvertLetterCase(this->_Character);
	}
};

