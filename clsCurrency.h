#pragma once
#include "clsString.h"
#include <fstream>

class clsCurrency
{
private:
	enum enMode { EMPTY_MODE, UPDATE_MODE };

	enMode _Mode;
	std::string _Country;
	std::string _CurrencyCode;
	std::string _CurrencyName;
	float _Rate;

	/*static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(std::string Line, std::string Separator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;

		std::vector <std::string> LoginRegisterDataRecord = clsString::SplitString(Line, Separator);

		LoginRegisterRecord.DateTime = LoginRegisterDataRecord[0];
		LoginRegisterRecord.UserName = LoginRegisterDataRecord[1];
		LoginRegisterRecord.Password = clsUtils::DecryptText(LoginRegisterDataRecord[2]);
		LoginRegisterRecord.Permissions = std::stoi(LoginRegisterDataRecord[3]);

		return LoginRegisterRecord;
	}*/

	static clsCurrency _ConvertLineToCurrencyObject(std::string Line, std::string Separator = "#//#")
	{
		std::vector<std::string> _CurrencyData;
		_CurrencyData = clsString::SplitString(Line, Separator);

		return clsCurrency(
			enMode::UPDATE_MODE, _CurrencyData[0],
			_CurrencyData[1], _CurrencyData[2],
			std::stof(_CurrencyData[3])
		);
	}

	static std::string _ConvertCurrencyObjectToLine(clsCurrency Currency, std::string Separator = "#//#")
	{
		std::string _CurrencyRecord = "";

		_CurrencyRecord += Currency.GetCountry() + Separator;
		_CurrencyRecord += Currency.GetCurrencyCode() + Separator;
		_CurrencyRecord += Currency.GetCurrencyName() + Separator;
		_CurrencyRecord += std::to_string(Currency.Rate);

		return _CurrencyRecord;
	}

	static std::vector<clsCurrency> _LoadCurrenciesDataFromFile()
	{
		std::vector<clsCurrency> _vCurrency;
		std::fstream _MyFile;

		_MyFile.open(Constant::FILE_CURRENCIES, std::ios::in);

		if (_MyFile.is_open())
		{
			std::string Line;
			while (getline(_MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				_vCurrency.push_back(Currency);
			}
			_MyFile.close();
		}

		return _vCurrency;
	}

	static void _SaveCurrenciesDataToFile(std::vector<clsCurrency> vCurrency)
	{
		std::fstream _MyFile;
		_MyFile.open(Constant::FILE_CURRENCIES, std::ios::out);

		std::string _DataLine;

		if (_MyFile.is_open())
		{
			for (clsCurrency Currency : vCurrency)
			{
				_DataLine = _ConvertCurrencyObjectToLine(Currency);
				_MyFile << _DataLine << std::endl;
			}
			_MyFile.close();
		}
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EMPTY_MODE, "", "", "", 0);
	}

	/*std::string _PrepareLoginRecord(std::string Separator = "#//#")
	{
		std::string LoginRecord = "";

		LoginRecord += clsDate::GetSystemDateTimeString() + Separator;
		LoginRecord += UserName + Separator;
		LoginRecord += clsUtils::EncryptText(Password) + Separator;
		LoginRecord += std::to_string(Permissions);

		return LoginRecord;
	}*/

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
		this->_AddDataLineToFile(this->_ConvertCurrencyObjectToLine(*this));
	}

	void _Update()
	{
		std::vector<clsCurrency> _vCurrencies = _LoadCurrenciesDataFromFile();

		for (clsCurrency& _Currency : _vCurrencies)
		{
			if (_Currency.GetCurrencyCode() == GetCurrencyCode() || _Currency.GetCurrencyName() == GetCurrencyName())
			{
				_Currency = *this;
				break;
			}
		}

		_SaveCurrenciesDataToFile(_vCurrencies);
	}

public:
	enum enSaveResult {
		SV_FAILED_EMPTY_OBJECT,
		SV_SUCCEEDED
	};

	clsCurrency(
		enMode Mode,
		std::string Currency,
		std::string CurrencyCode,
		std::string CurrencyName,
		float Rate
	)
	{
		this->_Mode = Mode;
		this->_Country = Currency;
		this->_CurrencyCode = CurrencyCode;
		this->_CurrencyName = CurrencyName;
		this->_Rate = Rate;
	}

	bool IsEmpty() const
	{
		return this->_Mode == enMode::EMPTY_MODE;
	}

	std::string GetCountry() { return this->_Country; }

	std::string GetCurrencyCode() { return this->_CurrencyCode; }

	std::string GetCurrencyName() { return this->_CurrencyName; }

	float GetRate() const { return this->_Rate; }

	void SetRate(float Rate) { this->_Rate = Rate; }

	__declspec(property(get = GetRate, put = SetRate)) float Rate;

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
		}
	}

	static clsCurrency FindByCurrencyCode(std::string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllLetterOfEachWord(CurrencyCode);

		std::fstream MyFile;
		MyFile.open(Constant::FILE_CURRENCIES, std::ios::in);

		if (MyFile.is_open())
		{
			std::string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (Currency.GetCurrencyCode() == CurrencyCode)
				{
					MyFile.close();
					return Currency;
				}
			}
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(std::string Country)
	{
		Country = clsString::UpperFirstLetterOfEachWord(clsString::LowerAllLetterOfEachWord(Country));

		std::fstream MyFile;
		MyFile.open(Constant::FILE_CURRENCIES, std::ios::in);

		if (MyFile.is_open())
		{
			std::string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::UpperFirstLetterOfEachWord(clsString::LowerAllLetterOfEachWord(Currency.GetCountry())) == Country)
				{
					MyFile.close();
					return Currency;
				}
			}
		}

		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(std::string CurrencyCode)
	{
		clsCurrency C1 = clsCurrency::FindByCurrencyCode(CurrencyCode);

		return (!C1.IsEmpty());
	}

	static std::vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesDataFromFile();
	}

	float ConvertToUSD(float Amount) const { return (Amount / Rate); }

	float ConvertToOtherCurrency(float Amount, clsCurrency DistenationCurrency) const
	{
		float AmountUSD = this->ConvertToUSD(Amount);

		if (DistenationCurrency.GetCurrencyCode() == "USD") return AmountUSD;

		return AmountUSD * DistenationCurrency.Rate;
	}
};

