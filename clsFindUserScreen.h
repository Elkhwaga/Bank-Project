#pragma once
#include "clsScreen.h"

class clsFindUserScreen : protected clsScreen
{
private:
	static void _PrintUser(clsUser User)
	{
		std::cout << "\nUser Card:";
		std::cout << "\n______________________________________________";
		std::cout << "\nFirst Name  : " << User.FirstName;
		std::cout << "\nLast Name   : " << User.LastName;
		std::cout << "\nFull Name   : " << User.GetFullName();
		std::cout << "\nEmail       : " << User.Email;
		std::cout << "\nPhone       : " << User.Phone;
		std::cout << "\nUser Name   : " << User.UserName;
		std::cout << "\nPassword    : " << User.Password;
		std::cout << "\nPermissions : " << User.Permissions;
		std::cout << "\n______________________________________________" << std::endl;
	}

	static std::string _ReadUserName()
	{
		return clsInputString::ReadString("\nPlease enter a user name: ");
	}

public:
	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("\t     Find user screen");
		std::string UserName = _ReadUserName();

		while (!clsUser::IsUserExist(UserName))
		{
			std::cout << "\nuser name [" << UserName << "] is already used, choose another one:\n";
			UserName = _ReadUserName();
		}

		clsUser User = clsUser::Find(UserName);

		if (!User.IsEmpty())
			std::cout << "\nUser Found :-)\n";
		else
			std::cout << "\nUser was not found :-(\n";

		_PrintUser(User);
	}
};

