#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"

class clsWithdrawScreen : protected clsScreen
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
	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("\t\tWithdraw Screen");

		std::string AccountNumber = _ReadAccountNumber();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			std::cout << "\naccount number [" << AccountNumber << "] is not found, choose another one:\n";
			AccountNumber = _ReadAccountNumber();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);

		double Amount = clsInputNumber::ReadPositiveDoubleNumber("\nPlease enter a withdraw mount: ");

		char Choice = clsInputString::ReadChoice("\nAre you sure you want to preform this transaction [Y/N]: ");

		if (clsEnums::IsContinue(Choice) == Enum::ChoiceStatus::YES)
		{
			if (Client.Withdraw(Amount))
			{
				std::cout << "\nAmount withdraw successfully.\n";
				std::cout << "\nNew balance is: " << Client.AccountBalance;
			}
			else
			{
				std::cout << "\ncan not withdraw, Insufficient Balance!.\n";
				std::cout << "Amount withdraw is: " << Amount;
				std::cout << "\nYour balance is: " << Client.AccountBalance << std::endl;
			}
		}
		else
			std::cout << "\nOperation was canceled.\n";
	}
};

