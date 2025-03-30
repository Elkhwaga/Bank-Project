#pragma once
#include "clsInputValidation.h"
#include "clsUtils.h"
#include "Constant.h"
#include "clsError.h"
#include <iomanip>
#include <string>

class clsInputNumber
{
public:

	static int RandomNumber(int MinNumber, int MaxNumber)
	{
		return std::rand() % (MaxNumber - MinNumber + 1) + MinNumber;
	}

	static float ReadNumber(const std::string& Message)
	{
		float Number;

		do
		{
			std::cout << Message;
			std::cin >> Number;

			if (std::cin.fail())
			{
				clsUtils::ClearInputBuffer(); // Reset the input stream in case of an error
				std::cout << "Invalid input. Please enter a positive integer." << std::endl;
			}

			break;

		} while (true);

		return Number;
	}

	static int ReadPositiveNumber(std::string& Message)
	{
		int Number = 0;

		do
		{
			std::cout << Message;
			std::cin >> Number;

			if (std::cin.fail() || Number < 0) // Check if the input is valid, positive, and not too large
			{
				clsUtils::ClearInputBuffer(); // Reset the input stream in case of an error
				std::cout << "Invalid input. Please enter a positive integer." << std::endl;
				Number = -1; // To prompt the user again
			}
		} while (Number < 0); // Continue until a valid positive integer is entered

		return Number;
	}

	static float ReadPositiveFloatNumber(const std::string& Message)
	{
		float Number = 0;
		do
		{
			std::cout << Message;
			std::cin >> Number;

			if (std::cin.fail() || Number < 0)
			{
				clsUtils::ClearInputBuffer(); // Reset the input stream in case of an error
				std::cout << "Invalid input. Please enter a positive integer." << std::endl;
				Number = -1; // To prompt the user again
			}
		} while (Number < 0);

		return Number;
	}

	static double ReadPositiveDoubleNumber(const std::string& Message)
	{
		double Number = 0;

		do
		{
			std::cout << Message;
			std::cin >> Number;

			if (std::cin.fail() || Number < 0)
			{
				clsUtils::ClearInputBuffer(); // Reset the input stream in case of an error
				std::cout << "Invalid input. Please enter a positive integer." << std::endl;
				Number = -1; // To prompt the user again
			}
		} while (Number < 0);

		return Number;
	}

	static int ReadNumberInRange(const std::string& Message, int MinNumber, int MaxNumber, short CustomSpaces)
	{
		int Number = 0;
		std::cout << std::left << std::setw(CustomSpaces) << "" << Message;
		std::cin >> Number;

		while (!clsInputValidation::IsNumberInRange(Number, MinNumber, MaxNumber))
		{
			clsUtils::ClearInputBuffer();
			std::cout << std::left << std::setw(CustomSpaces) << "" <<
				"Invalid input. Please enter a non-negative integer between " << MinNumber << " and " << MaxNumber << ": ";
			std::cin >> Number;
		}
		return Number;
	}

	static float ReadNumberInRange(const std::string& Message, float MinNumber, float MaxNumber)
	{
		float Number;
		std::cout << Message;
		std::cin >> Number;

		while (!clsInputValidation::IsNumberInRange(Number, MinNumber, MaxNumber))
		{
			clsUtils::ClearInputBuffer();
			std::cout << "Invalid input. Please enter a non-negative integer between " << MinNumber << " and " << MaxNumber << std::endl;
			std::cin >> Number;
		}
		return Number;
	}

	static float ReadNumberCustom(std::string& Message, bool AllowNegative)
	{
		int Attempts = 0;

		while (Attempts < Constant::MAX_RETRIES)
		{
			std::cout << "\n"
				<< Message << std::endl;
			float Number;

			// Attempt to read the Number
			if (!(std::cin >> Number))
			{
				clsUtils::ClearInputBuffer();
				std::cerr << clsError::FormatErrorMessage(Constant::ERROR_INVALID_NUMBER, Constant::MAX_RETRIES - Attempts - 1) << std::endl;
				Attempts++;
				continue;
			}

			clsUtils::ClearInputBuffer();

			// Validate Number range
			if (abs(Number) > std::numeric_limits<float>::max() / 2)
			{
				std::cerr << clsError::FormatErrorMessage(Constant::ERROR_OUT_OF_RANGE, Constant::MAX_RETRIES - Attempts - 1) << std::endl;
				Attempts++;
				continue;
			}

			// Check for negative Numbers when not allowed
			if (!AllowNegative && Number < 0)
			{
				std::cerr << clsError::FormatErrorMessage(Constant::ERROR_NEGATIVE_NOT_ALLOWED, Constant::MAX_RETRIES - Attempts - 1) << std::endl;
				Attempts++;
				continue;
			}

			return Number;
		}

		throw std::runtime_error(Constant::ERROR_MAX_ATTEMPTS);
	}

	static int ReadNumberWithAttempts(const std::string& Message, const int MinNumber, const int MaxNumber, short Attempts)
	{
		int Number;

		while (Attempts < 3)
		{
			std::cout << "Enter a Number: ";

			if (std::cin >> Number && clsInputValidation::IsNumberInRange(Number, MinNumber, MaxNumber))
			{
				return Number;
			}
			else
			{
				Attempts++;

				std::cout << "Error: Invalid input please enter an integer between "
					<< MinNumber << " AND " << MaxNumber << ".\n";
				clsUtils::ClearInputBuffer();
			}
		}
		return -1;
	}

	static bool ReadYesNo(const std::string& Message)
	{
		std::cout << Message;
		bool AllowNegative;

		if (!(std::cin >> AllowNegative))
		{
			throw std::runtime_error("Invalid input for negative Number selection");
		}
		std::cin.ignore();

		std::cout << "\nMode: " << (AllowNegative ? "Accepting all Numbers" : "Positive Numbers only") << std::endl;

		return AllowNegative;
	}
};

