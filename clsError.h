#pragma once
#include <iostream>
#include <sstream>

class clsError
{
public:
	/**
	 * @brief Generates a detailed error message with remaining attempts
	 * @param baseMessage The primary error message
	 * @param remainingAttempts Number of attempts left
	 * @return Formatted error message string
	 */
	static std::string FormatErrorMessage(const std::string& BaseMessage, int RemainingAttempts)
	{
		std::stringstream ss;
		ss << BaseMessage << "\n"
			<< "Remaining attempts: " << RemainingAttempts << "\n"
			<< "Please try again...";
		return ss.str();
	}
};

