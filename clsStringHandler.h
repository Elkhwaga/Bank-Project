#pragma once

#include "clsString.h"
#include "clsCharacter.h"
#include "clsStringCheck.h"
#include <iostream>

class clsHandler : public clsString, public clsCharacter, public clsStringCheck
{
public:
	clsHandler()
	{
		this->_Value = "";
		this->_Character = 0;
	}

	clsHandler(std::string Value)
	{
		this->_Value = Value;
	}

	clsHandler(char Character)
	{
		this->_Character = Character;
	}

	clsHandler(std::string Value, char Character)
	{
		this->_Value = Value;
		this->_Character = Character;
	}

	static std::string InvertAllLetterOfEachWord(std::string Str)
	{
		for (int i = 0; i < Str.length(); i++)
		{
			Str[i] = InvertLetterCase(Str[i]);
		}
		return Str;
	}

	std::string InvertAllLetterOfEachWord()
	{
		return this->InvertAllLetterOfEachWord(this->_Value);
	}

	static std::string GetAllVowel(std::string Str)
	{
		std::string StrTemp = "";
		for (int i = 0; i < Str.length(); i++)
		{
			if (IsVowel(Str[i]))
			{
				StrTemp += Str[i] + " ";
			}
		}
		return StrTemp;
	}

	std::string GetAllVowel()
	{
		return GetAllVowel(this->_Value);
	}

	static int CountVowel(std::string Str)
	{
		int Count = 0;
		// Count the number of vowels in the string

		for (int i = 0; i < Str.length(); i++)
		{
			if (IsVowel(Str[i]))
			{
				Count++;
			}
		}
		return Count;
	}

	int CountVowel()
	{
		return this->CountVowel(this->_Value);
	}

	static void DisplayFirstLetterOfEachWord(std::string Str)
	{
		bool IsFirstLetter = true;
		std::cout << "\nFirst letter of each word: " << std::endl;

		for (int i = 0; i < Str.length(); i++)
		{
			if (IsFirstLetter && Str[i] != ' ')
			{
				std::cout << Str[i] << std::endl;
				IsFirstLetter = false;
			}
			else if (Str[i] == ' ')
			{
				IsFirstLetter = true;
			}
		}
		std::cout << std::endl;
	}

	void DisplayFirstLetterOfEachWord()
	{
		this->DisplayFirstLetterOfEachWord(this->_Value);
	}

	static void DisplayAllVowel(std::string Str)
	{
		std::cout << "Vowels in string are: ";
		for (int i = 0; i < Str.length(); i++)
		{
			if (IsVowel(Str[i]))
			{
				std::cout << Str[i] << " ";
			}
		}
		std::cout << std::endl;
	}

	void DisplayAllVowel()
	{
		this->DisplayAllVowel(this->_Value);
	}

	static void DisplayEachWordInString(std::string Str, std::string Delim)
	{

		std::cout << "Your string words are:\n";
		short Pos = 0;
		std::string Word;
		while ((Pos = Str.find(Delim)) != std::string::npos)
		{
			Word = Str.substr(0, Pos);
			if (Word != "")
			{
				std::cout << Word << std::endl;
			}
			Str.erase(0, Pos + Delim.length());
		}
		if (Str != "")
		{
			std::cout << Str << std::endl;
		}
	}

	void DisplayEachWordInString(std::string Delim)
	{
		this->DisplayEachWordInString(this->_Value, Delim);
	}
};

