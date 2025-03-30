#pragma once
#include "InterfaceCommunication.h"

class clsPerson : public InterfaceCommunication
{
private:
	std::string _FirstName;
	std::string _LastName;
	std::string _Email;
	std::string _Phone;

public:
	clsPerson(
		std::string FirstName,
		std::string LastName,
		std::string Email,
		std::string Phone
	)
	{
		this->_FirstName = FirstName;
		this->_LastName = LastName;
		this->_Email = Email;
		this->_Phone = Phone;
	}

	void SetFirstName(std::string FirstName)
	{
		this->_FirstName = FirstName;
	}

	std::string GetFirstName()
	{
		return this->_FirstName;
	}

	__declspec(property(get = GetFirstName, put = SetFirstName)) std::string FirstName;

	void SetLastName(std::string LastName)
	{
		this->_LastName = LastName;
	}

	std::string GetLastName()
	{
		return this->_LastName;
	}

	__declspec(property(get = GetLastName, put = SetLastName)) std::string LastName;

	void SetEmail(std::string Email)
	{
		this->_Email = Email;
	}

	std::string GetEmail()
	{
		return this->_Email;
	}

	__declspec(property(get = GetEmail, put = SetEmail)) std::string Email;

	void SetPhone(std::string Phone)
	{
		this->_Phone = Phone;
	}

	std::string GetPhone()
	{
		return this->_Phone;
	}

	__declspec(property(get = GetPhone, put = SetPhone)) std::string Phone;

	std::string GetFullName() const
	{
		return this->_FirstName + " " + this->_LastName;
	}

	void SendEmail(std::string Title, std::string Body)
	{
		std::cout << "\nThe following message send successfully to email: " << this->_Email;
		std::cout << "\nTitle: " << Title;
		std::cout << "\nBody: " << Body;
	}

	void SendSMS(std::string TextMessage)
	{
		std::cout << "\nThe following message send successfully to phone: " << this->_Phone;
		std::cout << "\n" << TextMessage;
	}
};

