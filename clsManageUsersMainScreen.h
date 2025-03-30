#pragma once
#include "clsScreen.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUsersMainScreen : protected clsScreen
{
private:
	enum enManageUsersMenuOptions
	{
		SHOW_USERS_LIST = 1,
		ADD_NEW_USER,
		DELETE_USER,
		UPDATE_USER,
		FIND_USER,
		MAIN_MENU
	};

	static enManageUsersMenuOptions _ReadManageUsersMenuOption()
	{
		std::cout << std::left << std::setw(37) << "" << "\tChoose what do you want to do? [1 to 6]\n";
		short _Choice = clsInputNumber::ReadNumberInRange("\tEnter number between 1 to 6: ", 1, 6, 37);
		return static_cast<enManageUsersMenuOptions>(_Choice);
	}

	static void _ShowAllUsersScreen()
	{
		clsUsersListScreen::ShowUsersList();
	}

	static void _ShowAddNewUserScreen()
	{
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUserScreen()
	{
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen()
	{
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _GoBackToManageUsersMenu()
	{
		clsUtils::Pause("\n\nPress any key to go back to manage users menu ...\n");
		ShowManageUsersMenu();
	}

	static void _PerfromManageUsersMenuOption(enManageUsersMenuOptions UsersMenuOption)
	{
		switch (UsersMenuOption)
		{
		case clsManageUsersMainScreen::SHOW_USERS_LIST:
			clsUtils::ClearScreen();
			_ShowAllUsersScreen();
			_GoBackToManageUsersMenu();
			break;

		case clsManageUsersMainScreen::ADD_NEW_USER:
			clsUtils::ClearScreen();
			_ShowAddNewUserScreen();
			_GoBackToManageUsersMenu();
			break;

		case clsManageUsersMainScreen::DELETE_USER:
			clsUtils::ClearScreen();
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenu();
			break;

		case clsManageUsersMainScreen::UPDATE_USER:
			clsUtils::ClearScreen();
			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenu();
			break;

		case clsManageUsersMainScreen::FIND_USER:
			clsUtils::ClearScreen();
			_ShowFindUserScreen();
			_GoBackToManageUsersMenu();
			break;

		case clsManageUsersMainScreen::MAIN_MENU:
			break;
		}
	}

public:
	static void ShowManageUsersMenu()
	{
		if (!CheckAccessRights(clsUser::enPermissions::MANAGE_USERS)) return;

		clsUtils::ClearScreen();

		_DrawScreenHeader("\t     Manage Users Screen");

		std::cout << std::left << std::setw(37) << "" << "\t=============================================\n";
		std::cout << std::left << std::setw(37) << "" << "\t\t\tManage Users Menu\n";
		std::cout << std::left << std::setw(37) << "" << "\t=============================================\n";
		std::cout << std::left << std::setw(37) << "" << "\t[1] Show User List.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[2] Add New User.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[3] Delete User.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[4] Update User.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[5] Find User.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[6] Main Menu.\n";
		std::cout << std::left << std::setw(37) << "" << "\t=============================================\n" << std::endl;

		_PerfromManageUsersMenuOption(_ReadManageUsersMenuOption());
	}
};

