#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputString.h"

class clsUpdateUserScreen : protected clsScreen
{
private:
	static void _ReadUserInfo(clsUser& User)
	{
		User.SetFirstName(clsInputString::ReadName("\nEnter a first name: "));
		User.SetLastName(clsInputString::ReadName("\nEnter a last name: "));
		User.SetEmail(clsInputString::ReadString("\nEnter a email: "));
		User.SetPhone(clsInputString::ReadPhoneNumber());
		User.SetPassword(clsInputString::ReadString("\nEnter a password: "));
		User.SetPermissions(_ReadPermissionsToSet());
	}

	static void _PrintUser(clsUser User)
	{
		std::cout << "\nUser Card:";
		std::cout << "\n______________________________________________";
		std::cout << "\nFirst Name  : " << User.FirstName;
		std::cout << "\nLast Name   : " << User.LastName;
		std::cout << "\nFull Name   : " << User.GetFullName();
		std::cout << "\nEmail       : " << User.Email;
		std::cout << "\nPhone       : " << User.Phone;
		std::cout << "\nUser Name   : " << User.UserName;
		std::cout << "\nPassword    : " << User.Password;
		std::cout << "\nPermissions : " << User.Permissions;
		std::cout << "\n______________________________________________" << std::endl;
	}

	static int _ReadPermissionsToSet()
	{
		int Permissions = 0;
		char Choice;

		std::cout << "\nWhat do you want to give access to?\n" << std::endl;

		Choice = clsInputString::ReadChoice("\nDo you want to give << Full >> access [Y/N]: ");
		if (clsEnums::IsContinue(Choice) == Enum::ChoiceStatus::YES) { return -1; }

		Choice = clsInputString::ReadChoice("\nDo you want to access << Show Client List >> [Y/N]: ");
		if (clsEnums::IsContinue(Choice) == Enum::ChoiceStatus::YES)
		{
			Permissions += clsUser::enPermissions::LIST_CLIENTS;
		}

		Choice = clsInputString::ReadChoice("\nDo you want to access << Add New Client >> [Y/N]: ");
		if (clsEnums::IsContinue(Choice) == Enum::ChoiceStatus::YES)
		{
			Permissions += clsUser::enPermissions::ADD_NEW_CLIENT;
		}

		Choice = clsInputString::ReadChoice("\nDo you want to access << Delete Client >> [Y/N]: ");
		if (clsEnums::IsContinue(Choice) == Enum::ChoiceStatus::YES)
		{
			Permissions += clsUser::enPermissions::DELETE_CLIENT;
		}

		Choice = clsInputString::ReadChoice("\nDo you want to access << Update Client >> [Y/N]: ");
		if (clsEnums::IsContinue(Choice) == Enum::ChoiceStatus::YES)
		{
			Permissions += clsUser::enPermissions::UPDATE_CLIENT;
		}

		Choice = clsInputString::ReadChoice("\nDo you want to access << Find Client >> [Y/N]: ");
		if (clsEnums::IsContinue(Choice) == Enum::ChoiceStatus::YES)
		{
			Permissions += clsUser::enPermissions::FIND_CLIENT;
		}

		Choice = clsInputString::ReadChoice("\nDo you want to access << Transactions >> [Y/N]: ");
		if (clsEnums::IsContinue(Choice) == Enum::ChoiceStatus::YES)
		{
			Permissions += clsUser::enPermissions::TRNASACTIONS;
		}

		Choice = clsInputString::ReadChoice("\nDo you want to access << Manage User >> [Y/N]: ");
		if (clsEnums::IsContinue(Choice) == Enum::ChoiceStatus::YES)
		{
			Permissions += clsUser::enPermissions::MANAGE_USERS;
		}

		Choice = clsInputString::ReadChoice("\nDo you want to access << Login Register >> [Y/N]: ");
		if (clsEnums::IsContinue(Choice) == Enum::ChoiceStatus::YES)
		{
			Permissions += clsUser::enPermissions::LOGIN_REGISTER;
		}

		Choice = clsInputString::ReadChoice("\nDo you want to access << Transfer Log >> [Y/N]: ");
		if (clsEnums::IsContinue(Choice) == Enum::ChoiceStatus::YES)
		{
			Permissions += clsUser::enPermissions::TRANSFER_LOG;
		}

		return Permissions;
	}

	static std::string _ReadUserName()
	{
		return clsInputString::ReadString("\nPlease enter a user name: ");
	}

public:
	static void ShowUpdateUserScreen()
	{
		_DrawScreenHeader("\tUpdate user screen");

		std::string UserName = _ReadUserName();

		while (!clsUser::IsUserExist(UserName))
		{
			std::cout << "\nuser name [" << UserName << "] is already used, choose another one:\n";
			UserName = _ReadUserName();
		}

		clsUser User = clsUser::Find(UserName);

		_PrintUser(User);

		std::cout << "\n\nUpdate user info:\n";
		std::cout << "______________________________________________________\n";

		_ReadUserInfo(User);

		char Choice = clsInputString::ReadChoice("\nAre you sure want to update thisuUser [Y/N]: ");

		if (clsEnums::IsContinue(Choice) == Enum::ChoiceStatus::YES)
		{
			clsUser::enSaveResult SaveResult;

			SaveResult = User.Save();

			switch (SaveResult)
			{
			case clsUser::enSaveResult::SV_SUCCEEDED:
			{
				std::cout << "\nuser name updated successfully :-)\n";
				_PrintUser(User);
				break;
			}
			case clsUser::enSaveResult::SV_FAILED_EMPTY_OBJECT:
			{
				std::cout << "\nError user name was not saved because it's empty";
				break;
			}
			}
		}
		else
			std::cout << "\nOperation was canceled.\n";

	}
};

