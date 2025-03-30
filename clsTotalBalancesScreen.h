#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"

class clsTotalBalancesScreen : protected clsScreen
{
private:
	static void _PrintClientRecordBalanceLine(clsBankClient Client)
	{
		std::cout << "| " << std::left << std::setw(15) << Client.GetAccountNumber();
		std::cout << "| " << std::left << std::setw(40) << Client.GetFullName();
		std::cout << "| " << std::left << std::setw(12) << Client.GetAccountBalance();
		std::cout << "|";
	}

public:
	static void ShowTotalBalancesScreen()
	{
		std::vector<clsBankClient> vClients = clsBankClient::GetClientList();

		std::string Title = "\t   Total Balances Screen";
		std::string SubTitle = "\tClient List (" + std::to_string(vClients.size()) + ") Client(s)";

		_DrawScreenHeader(Title, SubTitle);

		std::cout << "\n__________________________________________________________________________\n";
		std::cout << "| " << std::left << std::setw(15) << "Account Number";
		std::cout << "| " << std::left << std::setw(40) << "Client Name";
		std::cout << "| " << std::left << std::setw(12) << "Balance";
		std::cout << "|";
		std::cout << "\n__________________________________________________________________________\n";

		double TotalBalances = clsBankClient::GetTotalBalances();

		if (vClients.size() == 0)

			std::cout << "\t\t\t\tNo clients available in the system!";
		else
		{
			for (clsBankClient Client : vClients)
			{
				_PrintClientRecordBalanceLine(Client);
				std::cout << std::endl;
			}
		}
		std::cout << "__________________________________________________________________________\n" << std::endl;
		std::cout << "\t\t\t Total Balances = " << TotalBalances << std::endl;
		std::cout << "\t\t ( " << clsUtils::NumberToText((int)TotalBalances) << " )" << std::endl;
	}
};

