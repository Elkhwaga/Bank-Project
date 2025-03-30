#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"

class clsCurrenciesListScreen : protected clsScreen
{
private:
	static void _PrintCurrencyRecordLine(clsCurrency Currency)
	{
		std::cout << "| " << std::left << std::setw(30) << Currency.GetCountry();
		std::cout << "| " << std::left << std::setw(15) << Currency.GetCurrencyCode();
		std::cout << "| " << std::left << std::setw(45) << Currency.GetCurrencyName();
		std::cout << "| " << std::left << std::setw(10) << Currency.Rate;
		std::cout << "|";
	}

public:
	static void ShowCurrenciesListScreen()
	{
		std::vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
		std::string Title = "\t      Currency List Screen";
		std::string SubTitle = "\t\t(" + std::to_string(vCurrencies.size()) + ") Currencies";

		_DrawScreenHeader(Title, SubTitle);

		std::cout << "\n_____________________________________________________________________________________________________________\n";
		std::cout << "| " << std::left << std::setw(30) << "Country";
		std::cout << "| " << std::left << std::setw(15) << "Currency Code";
		std::cout << "| " << std::left << std::setw(45) << "Currency Name";
		std::cout << "| " << std::left << std::setw(10) << "Rate";
		std::cout << "|";
		std::cout << "\n_____________________________________________________________________________________________________________\n";

		if (vCurrencies.size() == 0)

			std::cout << "\t\t\t\tNo Currency available in the system!\n";
		else
		{
			for (clsCurrency Currency : vCurrencies)
			{
				_PrintCurrencyRecordLine(Currency);
				std::cout << std::endl;
			}
		}
		std::cout << "_____________________________________________________________________________________________________________\n" << std::endl;
	}
};

