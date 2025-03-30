#pragma once
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputString.h"
#include "clsInputNumber.h"
#include "clsEnums.h"
#include "clsUtils.h"
#include "Constant.h"
#include <fstream>

class clsUser : public clsPerson
{
private:
	enum enMode { EMPTY_MODE, UPDATE_MODE, ADD_NEW_MODE };

	enMode _Mode;
	std::string _UserName;
	std::string _Password;
	int _Permissions;
	bool _MarkedForDelete = false;
	struct stLoginRegisterRecord;

	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(std::string Line, std::string Separator = "#//#")
	{
		stLoginRegisterRecord _LoginRegisterRecord;

		std::vector <std::string> _vLoginRegisterDataRecord = clsString::SplitString(Line, Separator);

		_LoginRegisterRecord.DateTime = _vLoginRegisterDataRecord[0];
		_LoginRegisterRecord.UserName = _vLoginRegisterDataRecord[1];
		_LoginRegisterRecord.Password = clsUtils::DecryptText(_vLoginRegisterDataRecord[2]);
		_LoginRegisterRecord.Permissions = std::stoi(_vLoginRegisterDataRecord[3]);

		return _LoginRegisterRecord;
	}

	static clsUser _ConvertLineToUserObject(std::string Line, std::string Separator = "#//#")
	{
		std::vector<std::string> _vUserData = clsString::SplitString(Line, Separator);

		return clsUser(
			enMode::UPDATE_MODE, _vUserData[0],
			_vUserData[1], _vUserData[2],
			_vUserData[3], _vUserData[4],
			clsUtils::DecryptText(_vUserData[5]), std::stoi(_vUserData[6])
		);
	}

	static std::string _ConvertUserObjectToLine(clsUser User, std::string Separator = "#//#")
	{
		std::string _UserRecord = "";

		_UserRecord += User.FirstName + Separator;
		_UserRecord += User.LastName + Separator;
		_UserRecord += User.Email + Separator;
		_UserRecord += User.Phone + Separator;
		_UserRecord += User._UserName + Separator;
		_UserRecord += clsUtils::EncryptText(User._Password) + Separator;
		_UserRecord += std::to_string(User._Permissions);

		return _UserRecord;
	}

	static std::vector<clsUser> _LoadUsersDataFromFile()
	{
		std::vector<clsUser> _vUsers;
		std::fstream _MyFile;

		_MyFile.open(Constant::FILE_USER, std::ios::in);

		if (_MyFile.is_open())
		{
			std::string Line;
			while (getline(_MyFile, Line))
			{
				clsUser _User = _ConvertLineToUserObject(Line);
				_vUsers.push_back(_User);
			}
			_MyFile.close();
		}

		return _vUsers;
	}

	static void _SaveUsersDataToFile(std::vector<clsUser> vUsers)
	{
		std::fstream _MyFile;
		_MyFile.open(Constant::FILE_USER, std::ios::out);

		std::string _DataLine;

		if (_MyFile.is_open())
		{
			for (clsUser _User : vUsers)
			{
				if (_User.MarkedForDeleted() == false)
				{
					_DataLine = _ConvertUserObjectToLine(_User);
					_MyFile << _DataLine << std::endl;
				}
			}
			_MyFile.close();
		}
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EMPTY_MODE, "", "", "", "", "", "", 0);
	}

	std::string _PrepareLoginRecord(std::string Separator = "#//#")
	{
		std::string _LoginRecord = "";

		_LoginRecord += clsDate::GetSystemDateTimeString() + Separator;
		_LoginRecord += UserName + Separator;
		_LoginRecord += clsUtils::EncryptText(Password) + Separator;
		_LoginRecord += std::to_string(Permissions);

		return _LoginRecord;
	}

	void _AddDataLineToFile(std::string DataLine)
	{
		std::fstream _MyFile;
		_MyFile.open(Constant::FILE_USER, std::ios::out | std::ios::app);

		if (_MyFile.is_open())
		{
			_MyFile << DataLine << std::endl;
			_MyFile.close();
		}
	}

	void _AddNew()
	{
		this->_AddDataLineToFile(this->_ConvertUserObjectToLine(*this));
	}

	void _Update()
	{
		std::vector<clsUser> _vUsers = _LoadUsersDataFromFile();

		for (clsUser& _User : _vUsers)
		{
			if (_User.GetUserName() == UserName)
			{
				_User = *this;
				break;
			}
		}

		_SaveUsersDataToFile(_vUsers);
	}

public:
	enum enPermissions
	{
		ALL = -1,
		LIST_CLIENTS = 1,
		ADD_NEW_CLIENT = 2,
		DELETE_CLIENT = 4,
		UPDATE_CLIENT = 8,
		FIND_CLIENT = 16,
		TRNASACTIONS = 32,
		MANAGE_USERS = 64,
		LOGIN_REGISTER = 128,
		TRANSFER_LOG = 256,
		CURRENCY_EXCHANGE = 512
	};

	enum enSaveResult {
		SV_FAILED_EMPTY_OBJECT,
		SV_SUCCEEDED,
		SV_FAILED_ACCOUNT_NUMBER_EXISTS
	};

	struct stLoginRegisterRecord
	{
		std::string DateTime;
		std::string UserName;
		std::string Password;
		int Permissions;
	};

	clsUser(
		enMode Mode,
		std::string FirstName,
		std::string LastName,
		std::string Email,
		std::string Phone,
		std::string UserName,
		std::string Password,
		int Permissions
	) : clsPerson(FirstName, LastName, Email, Phone)
	{
		this->_Mode = Mode;
		this->_UserName = UserName;
		this->_Password = Password;
		this->_Permissions = Permissions;
	}

	bool IsEmpty() const { return this->_Mode == enMode::EMPTY_MODE; }

	bool MarkedForDeleted() const { return this->_MarkedForDelete; }

	void SetUserName(std::string UserName) { this->_UserName = UserName; }

	std::string GetUserName() { return this->_UserName; }

	__declspec(property(get = GetUserName, put = SetUserName)) std::string UserName;

	void SetPassword(std::string Password) { this->_Password = Password; }

	std::string GetPassword() { return this->_Password; }

	__declspec(property(get = GetPassword, put = SetPassword)) std::string Password;

	void SetPermissions(int Permissions) { this->_Permissions = Permissions; }

	int GetPermissions() const { return this->_Permissions; }

	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	enSaveResult Save()
	{
		switch (this->_Mode)
		{
		case enMode::EMPTY_MODE:
			if (IsEmpty())
				return enSaveResult::SV_FAILED_EMPTY_OBJECT;
			break;
		case enMode::UPDATE_MODE:
			this->_Update();
			return enSaveResult::SV_SUCCEEDED;
			break;
		case enMode::ADD_NEW_MODE:
			if (clsUser::IsUserExist(this->_UserName))
				return enSaveResult::SV_FAILED_ACCOUNT_NUMBER_EXISTS;
			else
			{
				this->_AddNew();
				this->_Mode = enMode::UPDATE_MODE;
				return enSaveResult::SV_SUCCEEDED;
			}
			break;
		}
	}

	bool Delete()
	{
		std::vector<clsUser> _vUsers;

		for (clsUser& User : _vUsers)
		{
			if (User.GetUserName() == this->_UserName)
			{
				User._MarkedForDelete = true;
				break;
			}
		}

		this->_SaveUsersDataToFile(_vUsers);

		*this = this->_GetEmptyUserObject();

		return true;
	}

	static clsUser Find(std::string UserName)
	{
		std::fstream MyFile;
		MyFile.open(Constant::FILE_USER, std::ios::in);

		if (MyFile.is_open())
		{
			std::string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(std::string UserName, std::string Password)
	{
		std::fstream MyFile;
		MyFile.open(Constant::FILE_USER, std::ios::in);

		if (MyFile.is_open())
		{
			std::string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName && User.Password == Password)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static bool IsUserExist(std::string UserName)
	{
		clsUser User = clsUser::Find(UserName);
		return (!User.IsEmpty());
	}

	static clsUser GetAddNewUserObject(std::string UserName)
	{
		return clsUser(enMode::ADD_NEW_MODE, "", "", "", "", UserName, "", 0);
	}

	static std::vector<clsUser> GetUserList()
	{
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermission(enPermissions Permissions) const
	{
		if (this->Permissions == enPermissions::ALL) return true;

		return ((Permissions & this->Permissions) == Permissions) ? true : false;
	}

	void RegisterLogin()
	{
		std::string DateLine = _PrepareLoginRecord();

		std::fstream MyFile;
		MyFile.open(Constant::FILE_LOGIN_REGISTER, std::ios::out | std::ios::app);

		if (MyFile.is_open())
		{
			MyFile << DateLine << std::endl;
			MyFile.close();
		}
	}

	static std::vector <stLoginRegisterRecord> GetLoginRegisterList()
	{
		std::vector <stLoginRegisterRecord> vLoginRegisterRecord;

		std::fstream MyFile;
		MyFile.open(Constant::FILE_LOGIN_REGISTER, std::ios::in);

		if (MyFile.is_open())
		{
			std::string Line;
			stLoginRegisterRecord LoginRegisterRecord;

			while (getline(MyFile, Line))
			{
				LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);
				vLoginRegisterRecord.push_back(LoginRegisterRecord);
			}

			MyFile.close();
		}

		return vLoginRegisterRecord;
	}
};

