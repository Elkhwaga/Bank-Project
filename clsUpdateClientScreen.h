#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputString.h"
#include "clsInputNumber.h"

class clsUpdateClientScreen : protected clsScreen
{
private:
	static void _ReadClientInfo(clsBankClient& Client)
	{
		Client.FirstName = clsInputString::ReadName("\nEnter a first name: ");
		Client.LastName = clsInputString::ReadName("\nEnter a last name: ");
		Client.Email = clsInputString::ReadString("\nEnter a email: ");
		Client.Phone = clsInputString::ReadPhoneNumber();
		Client.PinCode = clsInputString::ReadPinCode();
		Client.AccountBalance = clsInputNumber::ReadPositiveDoubleNumber("\nEnter a balance: ");
	}

	static void _PrintClient(clsBankClient Client)
	{
		std::cout << "\nClient Card:\n";
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
	static void ShowUpdateClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::UPDATE_CLIENT)) return;

		_DrawScreenHeader("\tUpdate client screen");

		std::string AccountNumber = _ReadAccountNumber();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			std::cout << "\naccount number [" << AccountNumber << "] is already used, choose another one:\n";
			AccountNumber = _ReadAccountNumber();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);

		std::cout << "\n\nUpdate client info:\n";
		std::cout << "______________________________________________________\n";

		_ReadClientInfo(Client);

		char Choice = clsInputString::ReadChoice("\nAre you sure want to update this client [Y/N]: ");

		if (clsEnums::IsContinue(Choice) == Enum::ChoiceStatus::YES)
		{
			clsBankClient::enSaveResult SaveResult;

			SaveResult = Client.Save();

			switch (SaveResult)
			{
			case clsBankClient::enSaveResult::SV_SUCCEEDED:
			{
				std::cout << "\nAccount updated successfully :-)\n";
				_PrintClient(Client);
				break;
			}
			case clsBankClient::enSaveResult::SV_FAILED_EMPTY_OBJECT:
			{
				std::cout << "\nError account was not saved because it's empty";
				break;
			}
			}
		}
		else
			std::cout << "\nOperation was canceled.\n";

	}
};

