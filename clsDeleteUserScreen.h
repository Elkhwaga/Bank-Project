#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputString.h"

class clsDeleteUserScreen : protected clsScreen
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
	static void ShowDeleteUserScreen()
	{
		_DrawScreenHeader("\t     Delete User Screen");

		std::string UserName = _ReadUserName();

		while (!clsUser::IsUserExist(UserName))
		{
			std::cout << "\n  user name [" << UserName << "] is already used, choose another one:\n";
			UserName = _ReadUserName();
		}

		clsUser User = clsUser::Find(UserName);

		_PrintUser(User);

		char Choice = clsInputString::ReadChoice("\nAre you sure want to delete this user [Y/N]: ");

		if (clsEnums::IsContinue(Choice) == Enum::ChoiceStatus::YES)
		{
			if (User.Delete())
			{
				std::cout << "\nUser deleted successfully :-)\n";
				_PrintUser(User);
			}
			else
			{
				std::cout << "\nError user was not deleted\n";
			}
		}
		else
			std::cout << "\nOperation was canceled.\n";
	}
};

