#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputNumber.h"
#include "clsInputString.h"
#include "clsEnums.h"

class clsTransferScreen : protected clsScreen
{
private:
	static void _PrintClient(clsBankClient Client)
	{
		std::cout << "\nClient Card:";
		std::cout << "\n______________________________________________";
		std::cout << "\nFull Name       : " << Client.GetFullName();
		std::cout << "\nAccount Number  : " << Client.GetAccountNumber();
		std::cout << "\nAccount Balance : " << Client.AccountBalance;
		std::cout << "\n______________________________________________" << std::endl;
	}

	static std::string _ReadAccountNumber(const std::string& Message)
	{
		std::cout << Message << std::endl;
		std::string AccountNumber;

		AccountNumber = clsInputString::ReadAccountNumber();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			std::cout << "\naccount number [" << AccountNumber << "] is not found, choose another one:\n";
			AccountNumber = clsInputString::ReadAccountNumber();
		}
		return AccountNumber;
	}

	static double _ReadAmount(clsBankClient SourceClient)
	{
		double Amount;
		Amount = clsInputNumber::ReadPositiveDoubleNumber("\nEnter Transfer Amount: ");

		while (Amount > SourceClient.AccountBalance)
		{
			std::cout << "\nAmount exceeds the available balance, enter a another amount:\n";
			Amount = clsInputNumber::ReadPositiveDoubleNumber("\nEnter Transfer Amount: ");
		}
		return Amount;
	}

public:
	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\tTransfer Screen");

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("\nPlease enter account number to transfer from:\n"));
		_PrintClient(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("\nPlease enter account number to transfer to:\n"));
		_PrintClient(DestinationClient);

		double Amount = _ReadAmount(SourceClient);

		char Choice = clsInputString::ReadChoice("\nAre you sure toy want to perform this operation [Y/N]: ");

		if (clsEnums::IsContinue(Choice) == Enum::ChoiceStatus::YES)
		{
			if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.UserName))
				std::cout << "\nTransfer done successfully\n";
			else
				std::cout << "\nTransfer filed\n";
		}
		else
		{
			std::cout << "\nOperation was canceled.\n";
			return;
		}

		_PrintClient(SourceClient);
		_PrintClient(DestinationClient);
	}
};

