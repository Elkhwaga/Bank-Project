#pragma once
#include "clsScreen.h"
#include "clsUtils.h"
#include "clsInputNumber.h"
#include "clsTransactionsMainScreen.h"
#include "clsManageClientsMainScreen.h"
#include "clsManageUsersMainScreen.h"
#include "clsCurrencyExchangeMainScreen.h"
#include "clsLoginScreen.h"
#include "clsLoginRegisterScreen.h"
#include "Global.h"
#include <iomanip>

class clsMainScreen : protected clsScreen
{
	enum enMainMenuOptions
	{
		MANAGE_CLIENTS = 1,
		MANAGE_USERS,
		TRANSACTIONS,
		LOGIN_REGISTER,
		CURRENCY_EXCHANGE,
		LOGOUT
	};

	static enMainMenuOptions _ReadMainMenuOption()
	{
		std::cout << std::left << std::setw(37) << "" << "\tChoose what do you want to do? [1 to 6]\n";
		short _Choice = clsInputNumber::ReadNumberInRange("\tEnter number between 1 to 6: ", 1, 6, 37);
		return static_cast<enMainMenuOptions>(_Choice);
	}

	static void _ShowManageClientsMainScreen()
	{
		clsManageClientsMainScreen::ShowManageClientsMenu();
	}

	static void _ShowManageUsersMainScreen()
	{
		clsManageUsersMainScreen::ShowManageUsersMenu();
	}

	static void _ShowTransactionsMainScreen()
	{
		clsTransactionsMainScreen::ShowTransactionsMenu();
	}

	static void _ShowCurrencyExchangeMainScreen()
	{
		clsCurrencyExchangeMainScreen::ShowCurrencyExchangeMenu();
	}

	static void _ShowLoginRegisterScreen()
	{
		clsLoginRegisterScreen::ShowLoginRegisterScreen();
	}

	static void _Logout()
	{
		CurrentUser = clsUser::Find("", "");
	}

	static void _GoBackToMainMenu()
	{
		clsUtils::Pause("\n\nPress any key to go back to main menu ...\n");
		ShowMainMenu();
	}

	static void _PerfromMainMenuOption(enMainMenuOptions MainMenuOption)
	{
		switch (MainMenuOption)
		{
		case clsMainScreen::MANAGE_CLIENTS:
			clsUtils::ClearScreen();
			_ShowManageClientsMainScreen();
			_GoBackToMainMenu();
			break;

		case clsMainScreen::MANAGE_USERS:
			clsUtils::ClearScreen();
			_ShowManageUsersMainScreen();
			_GoBackToMainMenu();
			break;

		case clsMainScreen::TRANSACTIONS:
			clsUtils::ClearScreen();
			_ShowTransactionsMainScreen();
			_GoBackToMainMenu();
			break;

		case clsMainScreen::LOGIN_REGISTER:
			clsUtils::ClearScreen();
			_ShowLoginRegisterScreen();
			_GoBackToMainMenu();
			break;

		case clsMainScreen::CURRENCY_EXCHANGE:
			clsUtils::ClearScreen();
			_ShowCurrencyExchangeMainScreen();
			_GoBackToMainMenu();
			break;

		case clsMainScreen::LOGOUT:
			clsUtils::ClearScreen();
			_Logout();
			break;
		}
	}

public:
	static void ShowMainMenu()
	{
		clsUtils::ClearScreen();

		_DrawScreenHeader("\t\tMain Screen");

		std::cout << std::left << std::setw(37) << "" << "\t=============================================\n";
		std::cout << std::left << std::setw(37) << "" << "\t\t\tMain Menu\n";
		std::cout << std::left << std::setw(37) << "" << "\t=============================================\n";
		std::cout << std::left << std::setw(37) << "" << "\t[1] Manage Clients.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[2] Manage Users.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[3] Transactions.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[4] Login Register.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[5] Currency Exchange.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[6] logout.\n";
		std::cout << std::left << std::setw(37) << "" << "\t=============================================\n" << std::endl;

		_PerfromMainMenuOption(_ReadMainMenuOption());
	}
};

