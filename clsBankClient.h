#pragma once
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputString.h"
#include "clsInputNumber.h"
#include "clsEnums.h"
#include "clsUtils.h"
#include "Constant.h"
#include <fstream>

class clsBankClient : public clsPerson
{
private:
	enum enMode { EMPTY_MODE = 0, UPDATE_MODE, ADD_NEW_MODE };

	enMode _Mode;
	std::string _AccountNumber;
	std::string _PinCode;
	double _AccountBalance;
	bool _MarkedForDelete = false;

	struct stTransferLogRecord;

	static clsBankClient _ConvertLineToClientObject(std::string Line, std::string Separator = "#//#")
	{
		std::vector<std::string> _vClientData;
		_vClientData = clsString::SplitString(Line, Separator);

		return clsBankClient(
			enMode::UPDATE_MODE, _vClientData[0],
			_vClientData[1], _vClientData[2],
			_vClientData[3], _vClientData[4],
			_vClientData[5], std::stod(_vClientData[6])
		);
	}

	static std::string _ConvertClientObjectToLine(clsBankClient Client, std::string Separator = "#//#")
	{
		std::string _ClientRecord = "";

		_ClientRecord += Client.GetFirstName() + Separator;
		_ClientRecord += Client.GetLastName() + Separator;
		_ClientRecord += Client.GetEmail() + Separator;
		_ClientRecord += Client.GetPhone() + Separator;
		_ClientRecord += Client._AccountNumber + Separator;
		_ClientRecord += Client._PinCode + Separator;
		_ClientRecord += std::to_string(Client._AccountBalance);

		return _ClientRecord;
	}

	static std::vector<clsBankClient> _LoadClientsDataFromFile()
	{
		std::vector<clsBankClient> _vClients;
		std::fstream _MyFile;

		_MyFile.open(Constant::FILE_CLIENT, std::ios::in);

		if (_MyFile.is_open())
		{
			std::string Line;
			while (getline(_MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				_vClients.push_back(Client);
			}
			_MyFile.close();
		}

		return _vClients;
	}

	static void _SaveClientsDataToFile(std::vector<clsBankClient> vClients)
	{
		std::fstream _MyFile;
		_MyFile.open(Constant::FILE_CLIENT, std::ios::out);

		std::string _DataLine;

		if (_MyFile.is_open())
		{
			for (clsBankClient _Client : vClients)
			{
				if (_Client.MarkedForDeleted() == false)
				{
					_DataLine = _ConvertClientObjectToLine(_Client);
					_MyFile << _DataLine << std::endl;
				}
			}
			_MyFile.close();
		}
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EMPTY_MODE, "", "", "", "", "", "", 0);
	}

	static stTransferLogRecord _ConvertTransferLogLineToRecord(std::string Line, std::string Separator = "#//#")
	{
		stTransferLogRecord _TransferLogRecord;

		std::vector <std::string> _TransferDataRecord = clsString::SplitString(Line, Separator);

		_TransferLogRecord.DateTime = _TransferDataRecord[0];
		_TransferLogRecord.SourceAccountNumber = _TransferDataRecord[1];
		_TransferLogRecord.DestinationAccountNumber = _TransferDataRecord[2];
		_TransferLogRecord.Amount = std::stod(_TransferDataRecord[3]);
		_TransferLogRecord.SourceBalanceAfter = std::stod(_TransferDataRecord[4]);
		_TransferLogRecord.DestinationBalanceAfter = std::stod(_TransferDataRecord[5]);
		_TransferLogRecord.UserName = _TransferDataRecord[6];

		return _TransferLogRecord;
	}

	std::string _PrepareTransferLogRecord(double Amount, clsBankClient& DestinationClient, std::string UserName, std::string Separator = "#//#")
	{
		std::string _TranferLogRecord = "";

		_TranferLogRecord += clsDate::GetSystemDateTimeString() + Separator;
		_TranferLogRecord += GetAccountNumber() + Separator;
		_TranferLogRecord += DestinationClient.GetAccountNumber() + Separator;
		_TranferLogRecord += std::to_string(Amount) + Separator;
		_TranferLogRecord += std::to_string(AccountBalance) + Separator;
		_TranferLogRecord += std::to_string(DestinationClient.AccountBalance) + Separator;
		_TranferLogRecord += UserName;

		return _TranferLogRecord;
	}

	void _RegisterTransferLog(double Amount, clsBankClient& DestinationClient, std::string UserName)
	{
		std::string _DataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

		std::fstream _MyFile;
		_MyFile.open(Constant::FILE_TRANSFER_LOG, std::ios::out | std::ios::app);

		if (_MyFile.is_open())
		{
			_MyFile << _DataLine << std::endl;
			_MyFile.close();
		}
	}

	void _AddDataLineToFile(std::string DataLine)
	{
		std::fstream _MyFile;
		_MyFile.open(Constant::FILE_CLIENT, std::ios::out | std::ios::app);

		if (_MyFile.is_open())
		{
			_MyFile << DataLine << std::endl;
			_MyFile.close();
		}
	}

	void _AddNew()
	{
		this->_AddDataLineToFile(this->_ConvertClientObjectToLine(*this));
	}

	void _Update()
	{
		std::vector<clsBankClient> _vClients = _LoadClientsDataFromFile();

		for (clsBankClient& _Client : _vClients)
		{
			if (_Client.GetAccountNumber() == GetAccountNumber())
			{
				_Client = *this;
				break;
			}
		}

		_SaveClientsDataToFile(_vClients);
	}

public:
	enum enSaveResult {
		SV_FAILED_EMPTY_OBJECT,
		SV_SUCCEEDED,
		SV_FAILED_ACCOUNT_NUMBER_EXISTS
	};

	struct stTransferLogRecord
	{
		std::string DateTime;
		std::string SourceAccountNumber;
		std::string DestinationAccountNumber;
		double Amount;
		double SourceBalanceAfter;
		double DestinationBalanceAfter;
		std::string UserName;
	};

	clsBankClient(
		enMode Mode,
		std::string FirstName,
		std::string LastName,
		std::string Email,
		std::string Phone,
		std::string AccountNumber,
		std::string PinCode,
		float AccountBalance
	) : clsPerson(FirstName, LastName, Email, Phone)
	{
		this->_Mode = Mode;
		this->_AccountNumber = AccountNumber;
		this->_PinCode = PinCode;
		this->_AccountBalance = AccountBalance;
	}

	bool IsEmpty() const
	{
		return this->_Mode == enMode::EMPTY_MODE;
	}

	bool MarkedForDeleted() const
	{
		return this->_MarkedForDelete;
	}

	std::string GetAccountNumber()
	{
		return this->_AccountNumber;
	}

	void SetPinCode(std::string PinCode)
	{
		this->_PinCode = PinCode;
	}

	std::string GetPinCode()
	{
		return this->_PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) std::string PinCode;

	void SetAccountBalance(double AccountBalance)
	{
		this->_AccountBalance = AccountBalance;
	}

	double GetAccountBalance() const
	{
		return this->_AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;

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
			if (clsBankClient::IsClientExist(this->_AccountNumber))
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

	bool Deposit(double Amount)
	{
		if (Amount > 0)
		{
			this->_AccountBalance += Amount;
			this->Save();
		}
		return false;
	}

	bool Withdraw(double Amount)
	{
		if (this->_AccountBalance > Amount)
		{
			this->_AccountBalance -= Amount;
			this->Save();
			return true;
		}

		return false;
	}

	bool Transfer(double Amount, clsBankClient& DestinationClient, std::string UserName)
	{
		if (this->Withdraw(Amount))
		{
			DestinationClient.Deposit(Amount);
			_RegisterTransferLog(Amount, DestinationClient, UserName);
			return true;
		}

		return false;
	}

	bool Delete()
	{
		std::vector<clsBankClient> _vClients;

		for (clsBankClient& Client : _vClients)
		{
			if (Client.GetAccountNumber() == this->_AccountNumber)
			{
				Client._MarkedForDelete = true;
				break;
			}
		}

		this->_SaveClientsDataToFile(_vClients);

		*this = this->_GetEmptyClientObject();

		return true;
	}

	static clsBankClient Find(std::string AccountNumber)
	{
		std::fstream MyFile;
		MyFile.open(Constant::FILE_CLIENT, std::ios::in);

		if (MyFile.is_open())
		{
			std::string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.GetAccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(std::string AccountNumber, std::string PinCode)
	{
		std::fstream MyFile;
		MyFile.open(Constant::FILE_CLIENT, std::ios::in);

		if (MyFile.is_open())
		{
			std::string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.GetAccountNumber() == AccountNumber && Client.GetPinCode() == PinCode)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static bool IsClientExist(std::string AccountNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return (!Client.IsEmpty());
	}

	static clsBankClient GetAddNewClientObject(std::string AccountNumber)
	{
		return clsBankClient(enMode::ADD_NEW_MODE, "", "", "", "", AccountNumber, "", 0);
	}

	static std::vector<clsBankClient> GetClientList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances()
	{
		std::vector<clsBankClient> vClients = clsBankClient::GetClientList();
		double TotalBalances = 0;

		for (clsBankClient& Client : vClients)
		{
			TotalBalances += Client.AccountBalance;
		}
		return TotalBalances;
	}

	static std::vector<stTransferLogRecord> GetTransferLogList()
	{
		std::vector<stTransferLogRecord> vTransferLogRecord;

		std::fstream MyFile;
		MyFile.open(Constant::FILE_TRANSFER_LOG, std::ios::in);

		if (MyFile.is_open())
		{
			std::string Line;

			stTransferLogRecord TransferLogRecord;

			while (getline(MyFile, Line))
			{
				TransferLogRecord = _ConvertTransferLogLineToRecord(Line);
				vTransferLogRecord.push_back(TransferLogRecord);
			}

			MyFile.close();
		}

		return vTransferLogRecord;
	}
};

