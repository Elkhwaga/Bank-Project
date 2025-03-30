#pragma once
#include "clsScreen.h"
#include "clsUser.h"

class clsUsersListScreen : protected clsScreen
{
private:
	static void _PrintUserRecordLine(clsUser User)
	{
		std::cout << "| " << std::left << std::setw(20) << User.UserName;
		std::cout << "| " << std::left << std::setw(25) << User.GetFullName();
		std::cout << "| " << std::left << std::setw(12) << User.Phone;
		std::cout << "| " << std::left << std::setw(20) << User.Email;
		std::cout << "| " << std::left << std::setw(10) << User.Password;
		std::cout << "| " << std::left << std::setw(12) << User.Permissions;
		std::cout << "|";
	}

public:
	static void ShowUsersList()
	{
		std::vector<clsUser> vUsers = clsUser::GetUserList();
		std::string Title = "\t\tUser List Screen";
		std::string SubTitle = "\t     User List (" + std::to_string(vUsers.size()) + ") User(s)";

		_DrawScreenHeader(Title, SubTitle);

		std::cout << "\n________________________________________________________________________________________________________________\n";
		std::cout << "| " << std::left << std::setw(20) << "User Name";
		std::cout << "| " << std::left << std::setw(25) << "Full Name";
		std::cout << "| " << std::left << std::setw(12) << "Phone";
		std::cout << "| " << std::left << std::setw(20) << "Email";
		std::cout << "| " << std::left << std::setw(10) << "Password";
		std::cout << "| " << std::left << std::setw(12) << "Permissions";
		std::cout << "|";
		std::cout << "\n________________________________________________________________________________________________________________\n";

		if (vUsers.size() == 0)

			std::cout << "\t\t\t   No users available in the system!\n";
		else
		{
			for (clsUser User : vUsers)
			{
				_PrintUserRecordLine(User);
				std::cout << std::endl;
			}
		}
		std::cout << "________________________________________________________________________________________________________________\n" << std::endl;
	}
};

