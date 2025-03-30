#pragma once
#include <iostream>
#include <iomanip>
#include "clsDate.h";
#include "Global.h"

class clsScreen
{
protected:
	static void _DrawScreenHeader(std::string Title, std::string SubTitle = "")
	{
		std::cout << std::left << std::setw(40) << "" << "_____________________________________________\n\n";
		std::cout << std::left << std::setw(40) << "" << Title << "\n\n";
		if (SubTitle != "")
			std::cout << std::left << std::setw(40) << "" << SubTitle << "\n\n";
		std::cout << std::left << std::setw(40) << "" << "_____________________________________________\n" << std::endl;

		if (!CurrentUser.IsEmpty())
			std::cout << std::left << std::setw(40) << "" << "\t\tUser: " << CurrentUser.UserName << std::endl;

		std::cout << std::left << std::setw(40) << "" << "\t\tDate: " << clsDate::FormateDate(clsDate::DateToString(clsDate()), "mm/dd/yyyy") << std::endl;
		std::cout << std::left << std::setw(40) << "" << "_____________________________________________\n\n" << std::endl;

	}

	static bool CheckAccessRights(clsUser::enPermissions Permissions)
	{
		if (!CurrentUser.CheckAccessPermission(Permissions))
		{
			std::cout << std::left << std::setw(40) << "" << "_____________________________________________\n\n";
			std::cout << std::left << std::setw(40) << "" << "     Access denied! contact your admin\n";
			std::cout << std::left << std::setw(40) << "" << "_____________________________________________\n\n" << std::endl;
			return false;
		}
		else
			return true;
	}
};

