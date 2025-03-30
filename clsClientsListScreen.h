#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>

class clsClientsListScreen : protected clsScreen
{
	static void _PrintClientRecordLine(clsBankClient Client)
	{
		std::cout << "| " << std::left << std::setw(15) << Client.GetAccountNumber();
		std::cout << "| " << std::left << std::setw(20) << Client.GetFullName();
		std::cout << "| " << std::left << std::setw(12) << Client.Phone;
		std::cout << "| " << std::left << std::setw(20) << Client.Email;
		std::cout << "| " << std::left << std::setw(10) << Client.PinCode;
		std::cout << "| " << std::left << std::setw(12) << Client.AccountBalance;
		std::cout << "|";
	}

public:
	static void ShowClientsList()
	{
		if (!CheckAccessRights(clsUser::enPermissions::LIST_CLIENTS)) return;

		std::vector<clsBankClient> vClients = clsBankClient::GetClientList();
		std::string Title = "\t   Client List Screen";
		std::string SubTitle = "\tClient List (" + std::to_string(vClients.size()) + ") Client(s)";

		_DrawScreenHeader(Title, SubTitle);

		std::cout << "\n______________________________________________________________________________________________________\n";
		std::cout << "| " << std::left << std::setw(15) << "Account Number";
		std::cout << "| " << std::left << std::setw(20) << "Client Name";
		std::cout << "| " << std::left << std::setw(12) << "Phone";
		std::cout << "| " << std::left << std::setw(20) << "Email";
		std::cout << "| " << std::left << std::setw(10) << "Pin Code";
		std::cout << "| " << std::left << std::setw(12) << "Balance";
		std::cout << "|";
		std::cout << "\n______________________________________________________________________________________________________\n";

		if (vClients.size() == 0)

			std::cout << "\t\t\t\tNo clients available in the system!\n";
		else
		{
			for (clsBankClient Client : vClients)
			{
				_PrintClientRecordLine(Client);
				std::cout << std::endl;
			}
		}
		std::cout << "______________________________________________________________________________________________________\n" << std::endl;
	}
};

