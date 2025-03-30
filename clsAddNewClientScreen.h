#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputString.h"
#include "clsInputNumber.h"

class clsAddNewClientScreen : protected clsScreen
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
	static void ShowAddNewClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::ADD_NEW_CLIENT)) return;

		_DrawScreenHeader("\t    Add New Client Screen");

		std::string AccountNumber = _ReadAccountNumber();

		while (clsBankClient::IsClientExist(AccountNumber))
		{
			std::cout << "\naccount number [" << AccountNumber << "] is already used, choose another one:\n";
			AccountNumber = _ReadAccountNumber();
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

		std::cout << "\n\nAdd client info:\n";
		std::cout << "______________________________________________________\n";

		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResult SaveResult;

		SaveResult = NewClient.Save();

		switch (SaveResult)
		{
		case clsBankClient::enSaveResult::SV_SUCCEEDED:
			std::cout << "\nclient added successfully :-)\n";
			_PrintClient(NewClient);
			break;

		case clsBankClient::enSaveResult::SV_FAILED_EMPTY_OBJECT:
			std::cout << "\nError account was not saved because it's empty\n";
			break;

		case clsBankClient::enSaveResult::SV_FAILED_ACCOUNT_NUMBER_EXISTS:
			std::cout << "\nError account was not saved because account number used!\n";
			break;
		}
	}
};

