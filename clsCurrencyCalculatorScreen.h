#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputNumber.h"
#include "clsInputString.h"

class clsCurrencyCalculatorScreen : protected clsScreen
{
	static float _ReadAmount()
	{
		return clsInputNumber::ReadPositiveFloatNumber("\nEnter amount to exchange: ");
	}

	static clsCurrency _GetCurrency(const std::string& Message)
	{
		std::string CurrencyCode = "";
		CurrencyCode = clsInputString::ReadTextWithLength("\nPlease enter currency code: ", "Please enter a valid currency code.", 3);

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			std::cout << "\nCurrency is not found [" << CurrencyCode << "] choose another one:\n";
			CurrencyCode = clsInputString::ReadTextWithLength("\nPlease enter currency code: ", "Please enter a valid currency code.", 3);
		}

		clsCurrency Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);
		return Currency;
	}

	static void _PrintCurrencyCard(clsCurrency Currency, const std::string& Message)
	{
		std::cout << Message << "\n";
		std::cout << "___________________________________________";
		std::cout << "\nCountry      : " << Currency.GetCountry();
		std::cout << "\nCountry Code : " << Currency.GetCurrencyCode();
		std::cout << "\nCountry Name : " << Currency.GetCurrencyName();
		std::cout << "\nRate ($1)    : " << Currency.Rate;
		std::cout << "\n___________________________________________\n" << std::endl;
	}

	static void _PrintCalculationsResult(float Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo)
	{
		_PrintCurrencyCard(CurrencyFrom, "\nConvert From:");

		float AmountInUSD = CurrencyFrom.ConvertToUSD(Amount);

		if (CurrencyTo.GetCurrencyCode() == "USD")
		{
			std::cout << Amount << " " << CurrencyFrom.GetCurrencyCode() << " = "
				<< AmountInUSD << " Dollar." << std::endl;
			return;
		}

		_PrintCurrencyCard(CurrencyTo, "\nConvert To:");

		float AmountInCurrencyTo = CurrencyFrom.ConvertToOtherCurrency(Amount, CurrencyTo);

		std::cout << Amount << " " << CurrencyFrom.GetCurrencyCode() << " = "
			<< AmountInCurrencyTo << " " << CurrencyTo.GetCurrencyCode() << "." << std::endl;
	}

public:
	static void ShowCurrencyCalculatorScreen()
	{
		char Choice = 'Y';

		while (clsEnums::IsContinue(Choice) == Enum::ChoiceStatus::YES)
		{
			clsUtils::ClearScreen();

			_DrawScreenHeader("\t   Currency Calculator Screen");

			clsCurrency CurrencyFrom = _GetCurrency("\nPlease enter currency from code:");
			clsCurrency CurrencyTo = _GetCurrency("\nPlease enter currency to code:");

			float Amount = _ReadAmount();

			_PrintCalculationsResult(Amount, CurrencyFrom, CurrencyTo);

			Choice = clsInputString::ReadChoice("\nDo you want to preform another calculation currency [Y/N]: ");
		}
	}
};

