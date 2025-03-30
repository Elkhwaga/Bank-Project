#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputNumber.h"
#include "clsInputString.h"
#include "clsEnums.h"

class clsUpdateRateScreen : protected clsScreen
{
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

	static void _ReadRate(clsCurrency& Currency)
	{
		Currency.Rate = clsInputNumber::ReadPositiveFloatNumber("\nEnter new rate: ");
	}

	static clsCurrency _GetCurrency(const std::string& Message)
	{
		std::string CurrencyCode = "";
		CurrencyCode = clsInputString::ReadTextWithLength(Message, "Please enter a valid currency code.", 3);

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			std::cout << "\nCurrency is not found [" << CurrencyCode << "] choose another one:\n";
			CurrencyCode = clsInputString::ReadTextWithLength("\nPlease enter currency code: ", "Please enter a valid currency code.", 3);
		}

		clsCurrency Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);
		return Currency;
	}

public:
	static void ShowUpdateRateScreen()
	{
		_DrawScreenHeader("\t   Update Currency Screen");

		clsCurrency Currency = _GetCurrency("\nPlease enter currency code: ");

		_PrintCurrency(Currency);

		std::cout << "\n\nUpdate currency rate:\n";
		std::cout << "______________________________________________________\n";

		_ReadRate(Currency);

		char Choice = clsInputString::ReadChoice("\nAre you sure want to update the rate of this currency [Y/N]: ");

		if (clsEnums::IsContinue(Choice) == Enum::ChoiceStatus::YES)
		{
			clsCurrency::enSaveResult SaveResult;

			SaveResult = Currency.Save();

			switch (SaveResult)
			{
			case clsBankClient::enSaveResult::SV_SUCCEEDED:
				std::cout << "\nRate updated successfully :-)\n";
				_PrintCurrency(Currency);
				break;
			case clsBankClient::enSaveResult::SV_FAILED_EMPTY_OBJECT:
				std::cout << "\nError rate was not saved because it's empty";
				break;
			}
		}
		else
			std::cout << "\nOperation was canceled.\n";
	}
};

