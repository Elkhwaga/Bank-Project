#pragma once
#include "clsEnums.h"
#include <string>
#include <vector>

class clsString
{
protected:
	std::string _Value;

public:

	void SetValue(std::string Value)
	{
		this->_Value = Value;
	}

	std::string GetValue()
	{
		return this->_Value;
	}

	static std::string UpperFirstLetterOfEachWord(std::string Str)
	{
		bool isFirstLetter = true;

		for (int i = 0; i < Str.length(); i++)
		{
			if (isFirstLetter && Str[i] != ' ')
			{
				Str[i] = std::toupper(Str[i]);
				isFirstLetter = false;
			}
			else if (Str[i] == ' ')
			{
				isFirstLetter = true;
			}
		}
		return Str;
	}

	std::string UpperFirstLetterOfEachWord()
	{
		return this->UpperFirstLetterOfEachWord(this->_Value);
	}

	static std::string LowerFirstLetterOfEachWord(std::string Str)
	{
		bool IsFirstLetter = true;

		for (int i = 0; i < Str.length(); i++)
		{
			if (IsFirstLetter && Str[i] != ' ')
			{
				Str[i] = tolower(Str[i]);
				IsFirstLetter = false;
			}
			else if (Str[i] == ' ')
			{
				IsFirstLetter = true;
			}
		}
		return Str;
	}

	std::string LowerFirstLetterOfEachWord()
	{
		return this->LowerFirstLetterOfEachWord(this->_Value);
	}

	static std::string LowerAllLetterOfEachWord(std::string Str)
	{
		for (int i = 0; i < Str.length(); i++)
		{
			Str[i] = tolower(Str[i]);
		}
		return Str;
	}

	std::string LowerAllLetterOfEachWord()
	{
		return LowerAllLetterOfEachWord(this->_Value);
	}

	static std::string UpperAllLetterOfEachWord(std::string Str)
	{
		for (int i = 0; i < Str.length(); i++)
		{
			Str[i] = toupper(Str[i]);
		}
		return Str;
	}

	std::string UpperAllLetterOfEachWord()
	{
		return this->UpperAllLetterOfEachWord(this->_Value);
	}

	static std::string RemovePunctuationsFromString(std::string Str)
	{
		std::string Result = "";
		for (int i = 0; i < Str.length(); i++)
		{
			if (!ispunct(Str[i]))
			{
				Result += Str[i];
			}
		}
		return Result;
	}

	std::string RemovePunctuationsFromString()
	{
		return this->RemovePunctuationsFromString(this->_Value);
	}

	static std::string TrimLeft(std::string Str)
	{
		for (int i = 0; i < Str.length(); i++)
		{
			if (Str[i] != ' ')
				return Str.substr(i, Str.length() - i);
		}
		return "";
	}

	std::string TrimLeft()
	{
		return this->TrimLeft(this->_Value);
	}

	static std::string TrimRight(std::string Str)
	{
		for (int i = Str.length() - 1; i >= 0; i--)
		{
			if (Str[i] != ' ')
				return Str.substr(0, static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) + 1);
		}
		return "";
	}

	std::string TrimRight()
	{
		return this->TrimRight(this->_Value);
	}

	static std::string Trim(std::string Str)
	{
		return TrimLeft(TrimRight(Str));
	}

	std::string Trim()
	{
		return this->Trim(this->_Value);
	}

	static std::vector<std::string> SplitString(std::string Str, std::string Delim)
	{
		std::vector<std::string> vString;
		short Pos = 0;
		std::string Word;
		while ((Pos = Str.find(Delim)) != std::string::npos)
		{
			Word = Str.substr(0, Pos);

			vString.push_back(Word);

			Str.erase(0, Pos + Delim.length());
		}
		if (Str != "")
		{
			vString.push_back(Str);
		}
		return vString;
	}

	std::vector<std::string> SplitString(std::string Delim)
	{
		return this->SplitString(this->_Value, Delim);
	}

	static std::string JoinString(std::vector<std::string> vWord, std::string Delim)
	{
		std::string Str = "";
		for (std::string word : vWord)
		{
			Str += word + Delim;
		}
		return Str.substr(0, Str.length() - Delim.length());
	}

	static std::string JoinString(std::string Arr[], short Length, std::string Delim)
	{
		std::string Str = "";
		for (int i = 0; i < Length; i++)
		{
			Str += Arr[i] + Delim;
		}
		return Str.substr(0, Str.length() - Delim.length());
	}

	static std::string ReverseWordsInString(std::string Str, std::string Delim)
	{
		std::vector<std::string> vWord = SplitString(Str, Delim);
		std::string RevStr = "";
		std::vector<std::string>::iterator Iter = vWord.end();

		while (Iter != vWord.begin())
		{
			--Iter;
			RevStr += *Iter + " ";
		}
		return RevStr.substr(0, RevStr.length() - 1);
	}

	std::string ReverseWordsInString(std::string Delim)
	{
		return this->ReverseWordsInString(this->_Value, Delim);
	}

	static std::string ReplaceWordsInString(std::string Str, std::string OldWord, std::string NewWord)
	{
		int Pos = Str.find(OldWord);
		while (Pos != std::string::npos)
		{
			Str.replace(Pos, OldWord.length(), NewWord);
			Pos = Str.find(OldWord, Pos + NewWord.length());
		}

		return Str;
	}

	std::string ReplaceWordsInString(std::string OldWord, std::string NewWord)
	{
		return this->ReplaceWordsInString(this->_Value, OldWord, NewWord);
	}

	static std::string ReplaceWordsInStringUsingSplit(std::string Str, std::string OldWord, std::string NewWord, bool MatchCase, std::string Delim)
	{
		std::vector<std::string> vWord = SplitString(Str, Delim);

		for (std::string& Word : vWord)
		{
			if (MatchCase)
			{
				if (Word == OldWord)
					Word = NewWord;
			}
			else
			{
				if (LowerAllLetterOfEachWord(Word) == LowerAllLetterOfEachWord(OldWord))
					Word = NewWord;
			}
		}

		return JoinString(vWord, Delim);
	}

	std::string ReplaceWordsInStringUsingSplit(std::string OldWord, std::string NewWord, bool MatchCase, std::string Delim)
	{
		return this->ReplaceWordsInStringUsingSplit(this->_Value, OldWord, NewWord, MatchCase, Delim);
	}

	static std::string GetFirstLetterOfEachWord(std::string Str)
	{
		bool IsFirstLetter = true;
		std::string StrTemp = "";

		for (int i = 0; i < Str.length(); i++)
		{
			if (IsFirstLetter && Str[i] != ' ')
			{
				StrTemp += Str[i];
				IsFirstLetter = false;
			}
			else if (Str[i] == ' ')
			{
				IsFirstLetter = true;
			}
		}
		return StrTemp;
	}

	std::string GetFirstLetterOfEachWord()
	{
		return this->GetFirstLetterOfEachWord(this->_Value);
	}

	static std::string GetEachWordInString(std::string Str, std::string Delim)
	{
		int Pos = 0;
		std::string Word;
		while ((Pos = Str.find(Delim)) != std::string::npos)
		{
			Word = Str.substr(0, Pos);
			if (Word != "")
			{
				Word += Word;
			}
			Str.erase(0, Pos + Delim.length());
		}
		if (Str != "")
		{
			Word += Str;
		}
		return Word;
	}

	std::string GetEachWordInString(std::string Delim)
	{
		return this->GetEachWordInString(this->_Value, Delim);
	}

	static int CountAllSmallLetters(std::string Str)
	{
		int Counter = 0;

		for (int i = 0; i < Str.length(); i++)
		{
			if (clsEnums::GetCharacterCase(Str[i]) == Enum::CharacterCase::SMALL)
				Counter++;
		}

		return Counter;
	}

	int CountAllSmallLetters()
	{
		return this->CountAllSmallLetters(this->_Value);
	}

	static int CountAllCapitalLetters(std::string Str)
	{
		int Counter = 0;

		for (int i = 0; i < Str.length(); i++)
		{
			if (clsEnums::GetCharacterCase(Str[i]) == Enum::CharacterCase::CAPITAL)
				Counter++;
		}

		return Counter;
	}

	int CountAllCapitalLetters()
	{
		return this->CountAllCapitalLetters(this->_Value);
	}

	static int CountLetters(std::string Str, char CheckChar, bool MatchCase)
	{
		int Counter = 0;

		for (int i = 0; i < Str.length(); i++)
		{
			if (MatchCase)
			{
				if (Str[i] == CheckChar)
					Counter++;
			}
			else
			{
				if (tolower(Str[i]) == tolower(CheckChar))
					Counter++;
			}
		}

		return Counter;
	}

	int CountLetters(char CheckChar, bool MatchCase)
	{
		return this->CountLetters(this->_Value, CheckChar, MatchCase);
	}

	static int CountEachWordInString(std::string Str, std::string Delim)
	{
		int Count = 0;
		short Pos = 0;
		std::string word;
		while ((Pos = Str.find(Delim)) != std::string::npos)
		{
			word = Str.substr(0, Pos);
			if (word != "")
			{
				Count++;
			}
			Str.erase(0, Pos + Delim.length());
		}
		if (Str != "")
		{
			Count++;
		}
		return Count;
	}

	int CountEachWordInString(std::string Delim)
	{
		return this->CountEachWordInString(this->_Value, Delim);
	}

	static short Length(std::string Str)
	{
		return Str.length();
	}

	short Length()
	{
		return this->Length(this->_Value);
	}
};

