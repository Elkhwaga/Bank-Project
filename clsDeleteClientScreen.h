#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsEnums.h"

class clsDeleteClientScreen :protected clsScreen
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
	static void ShowDeleteClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::DELETE_CLIENT)) return;

		_DrawScreenHeader("\t    Delete Client Screen");

		std::string AccountNumber = _ReadAccountNumber();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			std::cout << "\naccount number [" << AccountNumber << "] is already used, choose another one:\n";
			AccountNumber = _ReadAccountNumber();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);

		char Choice = clsInputString::ReadChoice("\nAre you sure want to delete this client [Y/N]: ");

		if (clsEnums::IsContinue(Choice) == Enum::ChoiceStatus::YES)
		{
			if (Client.Delete())
			{
				std::cout << "\nClient deleted successfully :-)\n";
				_PrintClient(Client);
			}
			else
			{
				std::cout << "\nError client was not deleted\n";
			}
		}
		else
			std::cout << "\nOperation was canceled.\n";
	}
};

