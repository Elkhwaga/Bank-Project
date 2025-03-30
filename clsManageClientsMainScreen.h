#pragma once
#include "clsScreen.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsInputNumber.h"

class clsManageClientsMainScreen : protected clsScreen
{
private:
	enum enManageClientsMenuOptions
	{
		SHOW_CLIENTS_LIST = 1,
		ADD_NEW_CLIENT,
		DELETE_CLIENT,
		UPDATE_CLIENT,
		FIND_CLIENT,
		MAIN_MENU
	};

	static enManageClientsMenuOptions _ReadManageClientsMenuOption()
	{
		std::cout << std::left << std::setw(37) << "" << "\tChoose what do you want to do? [1 to 6]\n";
		short _Choice = clsInputNumber::ReadNumberInRange("\tEnter number between 1 to 6: ", 1, 6, 37);
		return static_cast<enManageClientsMenuOptions>(_Choice);
	}

	static void _ShowAllClientsScreen()
	{
		clsClientsListScreen::ShowClientsList();
	}

	static void _ShowAddNewClientScreen()
	{
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteClientScreen()
	{
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen()
	{
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen()
	{
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _GoBackToManageClientsMenu()
	{
		clsUtils::Pause("\n\nPress any key to go back to manage clients menu ...\n");
		ShowManageClientsMenu();
	}

	static void _PerfromManageClientsMenuOption(enManageClientsMenuOptions ClientsMenuOption)
	{
		switch (ClientsMenuOption)
		{
		case clsManageClientsMainScreen::SHOW_CLIENTS_LIST:
			clsUtils::ClearScreen();
			_ShowAllClientsScreen();
			_GoBackToManageClientsMenu();
			break;

		case clsManageClientsMainScreen::ADD_NEW_CLIENT:
			clsUtils::ClearScreen();
			_ShowAddNewClientScreen();
			_GoBackToManageClientsMenu();
			break;

		case clsManageClientsMainScreen::DELETE_CLIENT:
			clsUtils::ClearScreen();
			_ShowDeleteClientScreen();
			_GoBackToManageClientsMenu();
			break;

		case clsManageClientsMainScreen::UPDATE_CLIENT:
			clsUtils::ClearScreen();
			_ShowUpdateClientScreen();
			_GoBackToManageClientsMenu();
			break;

		case clsManageClientsMainScreen::FIND_CLIENT:
			clsUtils::ClearScreen();
			_ShowFindClientScreen();
			_GoBackToManageClientsMenu();
			break;

		case clsManageClientsMainScreen::MAIN_MENU:
			break;
		}
	}

public:
	static void ShowManageClientsMenu()
	{
		clsUtils::ClearScreen();

		_DrawScreenHeader("\t     Manage Clients Screen");

		std::cout << std::left << std::setw(37) << "" << "\t=============================================\n";
		std::cout << std::left << std::setw(37) << "" << "\t\t\tManage Clients Menu\n";
		std::cout << std::left << std::setw(37) << "" << "\t=============================================\n";
		std::cout << std::left << std::setw(37) << "" << "\t[1] Show Clients List.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[2] Add New Client.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[3] Delete Client.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[4] Update Client.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[5] Find Client.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[6] Main Menu.\n";
		std::cout << std::left << std::setw(37) << "" << "\t=============================================\n" << std::endl;

		_PerfromManageClientsMenuOption(_ReadManageClientsMenuOption());
	}
};

