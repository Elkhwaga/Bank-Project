#pragma once
#include "clsScreen.h"
#include "clsUser.h"

class clsLoginRegisterScreen : protected clsScreen
{
private:
	static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord LoginRegisterRecord)
	{
		std::cout << "| " << std::left << std::setw(25) << LoginRegisterRecord.DateTime;
		std::cout << "| " << std::left << std::setw(20) << LoginRegisterRecord.UserName;
		std::cout << "| " << std::left << std::setw(20) << LoginRegisterRecord.Password;
		std::cout << "| " << std::left << std::setw(15) << LoginRegisterRecord.Permissions;
		std::cout << "|";
	}

public:
	static void ShowLoginRegisterScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::LOGIN_REGISTER)) return;

		std::vector<clsUser::stLoginRegisterRecord> vLoginRegisterRecord = clsUser::GetLoginRegisterList();

		std::string Title = "\tLogin Register List Screen";
		std::string SubTitle = "\t\t(" + std::to_string(vLoginRegisterRecord.size()) + ") Register(s)";

		_DrawScreenHeader(Title, SubTitle);

		std::cout << "\n_________________________________________________________________________________________\n";
		std::cout << "| " << std::left << std::setw(25) << "Date Time";
		std::cout << "| " << std::left << std::setw(20) << "User Name";
		std::cout << "| " << std::left << std::setw(20) << "Password";
		std::cout << "| " << std::left << std::setw(15) << "Permissions";
		std::cout << "|";
		std::cout << "\n_________________________________________________________________________________________\n";

		if (vLoginRegisterRecord.size() == 0)

			std::cout << "\t\t\t   No registers available in the system!\n";
		else
		{
			for (clsUser::stLoginRegisterRecord LoginRegister : vLoginRegisterRecord)
			{
				_PrintLoginRegisterRecordLine(LoginRegister);
				std::cout << std::endl;
			}
		}
		std::cout << "_________________________________________________________________________________________\n" << std::endl;
	}
};

