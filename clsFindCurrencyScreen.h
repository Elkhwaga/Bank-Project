#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputString.h"
#include "clsInputNumber.h"

class clsFindCurrencyScreen : protected clsScreen
{
private:
	static void _PrintCurrency(clsCurrency Currency)
	{
		std::cout << "\nCurrency Card\n";
		std::cout << "_________________________________________\n";
		std::cout << "\nCountry       : " << Currency.GetCountry();
		std::cout << "\nCurrency Code : " << Currency.GetCurrencyCode();
		std::cout << "\nCurrency Name : " << Currency.GetCurrencyName();
		std::cout << "\nRate (1$) : " << Currency.Rate;
		std::cout << "\n_________________________________________\n";
	}

	static void _ShowResult(clsCurrency Currency)
	{
		if (Currency.IsEmpty())
			std::cout << "\n\nCurrency not found:-(\n";
		else
		{
			std::cout << "\n\nCurrency found :-)\n";
			_PrintCurrency(Currency);
		}
	}

public:
	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\t  Find Currency Screen");

		short Choice = clsInputNumber::ReadNumberInRange("\nPlease enter find by < [1] Code or [2] Country >: ", 1, 2);

		std::string Input;

		if (Choice == 1)
		{
			Input = clsInputString::ReadTextWithLength("\nPlease enter currency code: ", "Please enter a valid currency code.", 3);
			clsCurrency Currency = clsCurrency::FindByCurrencyCode(Input);
			_ShowResult(Currency);
			return;
		}

		Input = clsInputString::ReadString("\nPlease enter country Name: ");
		clsCurrency Currency = clsCurrency::FindByCountry(Input);
		_ShowResult(Currency);
	}
};

