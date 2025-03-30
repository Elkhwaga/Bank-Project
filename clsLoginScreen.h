#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "clsInputString.h"
#include "clsUtils.h"
#include "Global.h"

class clsLoginScreen : protected clsScreen
{
private:
	static bool _Login()
	{
		bool _LoginFaild = false;
		short _FaildLoginCount = 0;
		std::string _UserName, _Password;

		do
		{
			if (_LoginFaild)
			{
				_FaildLoginCount++;
				std::cout << std::left << std::setw(40) << "\n" << " Invalid user name or password\n";
				std::cout << std::left << std::setw(40) << "" << "You have " << (3 - _FaildLoginCount) << " Trial(s) to login.\n\n";
			}

			if (_FaildLoginCount == 3)
			{
				std::cout << std::left << std::setw(40) << "" << "Your are locked after 3 failed trails\n\n";
				return false;
			}

			_UserName = clsInputString::ReadString("Enter a user name: ", 40);
			_Password = clsInputString::ReadString("Enter a password: ", 40);

			CurrentUser = clsUser::Find(_UserName, _Password);
			_LoginFaild = CurrentUser.IsEmpty();

		} while (_LoginFaild);

		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainMenu();

		return true;
	}

public:
	static bool ShowLoginScreen()
	{
		clsUtils::ClearScreen();
		_DrawScreenHeader("\t\tLogin Screen");
		return _Login();
	}
};

