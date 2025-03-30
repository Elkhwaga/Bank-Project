#pragma once
#include "clsInputValidation.h"
#include "clsUtils.h"
#include "clsCheck.h"
#include <iostream>
#include <string>

class clsInputString
{
public:
	static std::string ReadString(const std::string& Message, short CustomSpaces = 0)
	{
		std::string Name;
		std::cout << std::left << std::setw(CustomSpaces) << "" << Message;
		std::getline(std::cin >> std::ws, Name);
		return Name;
	}

	static std::string ReadFullName(const std::string& Message)
	{
		std::string Name;
		while (true)
		{
			std::cout << Message;
			getline(std::cin >> std::ws, Name);

			// Check if the Name is valid
			if (!Name.empty() && Name.length() >= 3 && Name.length() <= 50)
			{
				break; // Exit the loop if the Name is valid
			}

			// If the Name is invalid, prompt the user again
			std::cout << "Invalid Name. The Name must be between 3 and 50 characters long. Please try again.\n";
		}

		return Name;
	}

	static std::string ReadName(const std::string& Message)
	{
		std::string Name;
		while (true)
		{
			std::cout << Message;
			std::cin >> Name;

			// Check if the Name is valid
			if (!Name.empty() && Name.length() >= 3 && Name.length() <= 10)
			{
				break; // Exit the loop if the Name is valid
			}

			// If the Name is invalid, prompt the user again
			std::cout << "Invalid Name. The Name must be between 3 and 50 characters long. Please try again.\n";
		}

		return Name;
	}

	static std::string ReadPhoneNumber()
	{
		std::string PhoneNumber;
		std::cout << "\nEnter a phone number: ";
		std::cin >> PhoneNumber;
		while (!clsInputValidation::IsDigitOnly(PhoneNumber) || !clsCheck::CheckLength(PhoneNumber, 11))
		{
			clsUtils::ClearInputBuffer();
			std::cout << "\nEnter a valid phone number: ";
			std::cin >> PhoneNumber;
		}
		return PhoneNumber;
	}

	static std::string ReadAccountNumber()
	{
		std::string AccountNumber;
		std::cout << "\nEnter an account number: ";
		std::cin >> AccountNumber;
		while (!clsCheck::CheckLength(AccountNumber, 4))
		{
			clsUtils::ClearInputBuffer();

			std::cout << "\nEnter a valid account number: ";
			std::cin >> AccountNumber;
		}
		return AccountNumber;
	}

	static std::string ReadPinCode()
	{
		std::string Input;
		std::cout << "\nEnter a 4-digit PIN: ";
		std::cin >> Input;
		while (!clsInputValidation::IsValidPinCodet(Input))
		{
			clsUtils::ClearInputBuffer();
			std::cout << "\nInvalid input. Please enter a 4-digit PIN: ";
			std::cin >> Input;
		}
		return Input;
	}

	static std::string ReadPassword() {
		std::cout << "\nEnter a Password: ";
		std::string Password;
		char c;

		// Use cin with special handling to capture input
		while (std::cin.get(c)) {
			if (c == '\n') break; // Stop capturing at newline

			// Echoing the entered character as an asterisk (*) for visual feedback
			std::cout << "*";

			// Add the character to our string
			Password += c;
		}

		return Password;
	}

	static char ReadDelem(const std::string& Message)
	{
		char Delem;
		std::cout << Message;
		while (!(std::cin >> Delem))
		{
			clsUtils::ClearInputBuffer();
			std::cout << "Please enter valid delem: ";
		}
		return Delem;
	}

	static char ReadChoice(const std::string& Message)
	{
		char Choice;
		std::cout << Message;
		while (!(std::cin >> Choice) || (Choice != 'Y' && Choice != 'y' && Choice != 'N' && Choice != 'n'))
		{
			clsUtils::ClearInputBuffer();
			std::cout << "Enter a valid choice: ";
		}
		return Choice;
	}

	static char ReadChar()
	{
		char Character;
		std::cout << "\nPlease enter a character: ";
		std::cin >> Character;
		return Character;
	}

	static std::string ReadTextWithLength(const std::string& Message, const std::string& ErrorMessage, short Length)
	{
		std::string text;
		std::cout << Message;
		std::cin >> text;
		if (text.length() != 3)
		{
			std::cout << ErrorMessage << std::endl;
			text = ReadTextWithLength(Message, ErrorMessage, Length);
		}

		// check if the password contains only alphabetic characters
		for (int i = 0; i < text.length(); i++)
		{
			if (!isalpha(text[i]))
			{
				std::cout << "text should contain only alphabetic characters" << std::endl;
				text = ReadTextWithLength(Message, ErrorMessage, Length);
			}
		}

		return text;
	}
};

