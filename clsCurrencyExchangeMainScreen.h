#pragma once
#include "clsScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
#include "clsUtils.h"

class clsCurrencyExchangeMainScreen : protected clsScreen
{
	enum enCurrencyExchangeMenuOptions
	{
		SHOW_CURRENCIES_LIST = 1,
		FIND_CURRENCY,
		UPDATE_CURRENCY,
		CURRENCY_CALCULATOR,
		MAIN_MENU
	};

	static enCurrencyExchangeMenuOptions _ReadCurrencyExchangeMenuOption()
	{
		std::cout << std::left << std::setw(37) << "" << "\tChoose what do you want to do? [1 to 5]\n";
		short _Choice = clsInputNumber::ReadNumberInRange("\tEnter number between 1 to 6: ", 1, 5, 37);
		return static_cast<enCurrencyExchangeMenuOptions>(_Choice);
	}

	static void _ShowCurrenciesListScreen()
	{
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}

	static void _ShowFindCurrencyScreen()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateRateScreen()
	{
		clsUpdateRateScreen::ShowUpdateRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen()
	{
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _GoBackToManageUsersMenu()
	{
		clsUtils::Pause("\n\nPress any key to go back to manage users menu ...\n");
		ShowCurrencyExchangeMenu();
	}

	static void _PerfromCurrencyExchangeMenuOption(enCurrencyExchangeMenuOptions CurrencyExchangeMenuOptions)
	{
		switch (CurrencyExchangeMenuOptions)
		{
		case clsCurrencyExchangeMainScreen::SHOW_CURRENCIES_LIST:
			clsUtils::ClearScreen();
			_ShowCurrenciesListScreen();
			_GoBackToManageUsersMenu();
			break;

		case clsCurrencyExchangeMainScreen::FIND_CURRENCY:
			clsUtils::ClearScreen();
			_ShowFindCurrencyScreen();
			_GoBackToManageUsersMenu();
			break;

		case clsCurrencyExchangeMainScreen::UPDATE_CURRENCY:
			clsUtils::ClearScreen();
			_ShowUpdateRateScreen();
			_GoBackToManageUsersMenu();
			break;

		case clsCurrencyExchangeMainScreen::CURRENCY_CALCULATOR:
			clsUtils::ClearScreen();
			_ShowCurrencyCalculatorScreen();
			_GoBackToManageUsersMenu();
			break;

		case clsCurrencyExchangeMainScreen::MAIN_MENU:
			break;
		}
	}

public:
	static void ShowCurrencyExchangeMenu()
	{
		if (!CheckAccessRights(clsUser::enPermissions::CURRENCY_EXCHANGE)) return;

		clsUtils::ClearScreen();

		_DrawScreenHeader("\t     Currency Exchange Screen");

		std::cout << std::left << std::setw(37) << "" << "\t=============================================\n";
		std::cout << std::left << std::setw(37) << "" << "\t\t\tCurrency Exchange Menu\n";
		std::cout << std::left << std::setw(37) << "" << "\t=============================================\n";
		std::cout << std::left << std::setw(37) << "" << "\t[1] Show Currencies List.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[2] Find Currency.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[3] Update Rate.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[4] Currency Calculator.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[5] Main Menu.\n";
		std::cout << std::left << std::setw(37) << "" << "\t=============================================\n" << std::endl;

		_PerfromCurrencyExchangeMenuOption(_ReadCurrencyExchangeMenuOption());
	}
};

