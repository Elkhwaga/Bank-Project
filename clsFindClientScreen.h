#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"

class clsFindClientScreen : clsScreen
{
private:
	static void _PrintClient(clsBankClient Client)
	{
		std::cout << "\nClient Card:";
		std::cout << "\n______________________________________________";
		std::cout << "\nFirst Name      : " << Client.FirstName;
		std::cout << "\nLast Name       : " << Client.LastName;
		std::cout << "\nFull Name       : " << Client.GetFullName();
		std::cout << "\nEmail           : " << Client.Email;
		std::cout << "\nPhone           : " << Client.Phone;
		std::cout << "\nAccount Number  : " << Client.GetAccountNumber();
		std::cout << "\nPin Code        : " << Client.PinCode;
		std::cout << "\nAccount Balance : " << Client.AccountBalance;
		std::cout << "\n______________________________________________" << std::endl;
	}
	static std::string _ReadAccountNumber()
	{
		return clsInputString::ReadAccountNumber();
	}

public:
	static void ShowFindClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::FIND_CLIENT)) return;

		_DrawScreenHeader("\t     Find client screen");
		std::string AccountNumber = _ReadAccountNumber();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			std::cout << "\naccount number [" << AccountNumber << "] is already used, choose another one:\n";
			AccountNumber = _ReadAccountNumber();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		if (!Client.IsEmpty())
			std::cout << "\nClient Found :-)\n";
		else
			std::cout << "\nClient was not found :-(\n";

		_PrintClient(Client);
	}
};

