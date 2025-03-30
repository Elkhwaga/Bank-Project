#pragma warning(disable : 4996)
#pragma once
#include "clsString.h"
#include "clsInputValidation.h"
#include "clsCheck.h"
#include "Enum.h"
#include <iostream>
#include <vector>
#include <ctime>

class clsDate
{
private:
	short _Day = 1;
	short _Month = 1;
	short _Year = 1900;

public:

	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		this->_Day = now->tm_mday;
		this->_Month = now->tm_mon + 1;
		this->_Year = now->tm_year + 1900;
	}

	clsDate(std::string sDate)
	{
		std::vector <std::string> vDate = clsString::SplitString(sDate, "/");

		this->_Day = stoi(vDate[0]);
		this->_Month = stoi(vDate[1]);
		this->_Year = stoi(vDate[2]);
	}

	clsDate(short Day, short Month, short Year)
	{
		this->_Day = Day;
		this->_Month = Month;
		this->_Year = Year;
	}

	clsDate(short DateOrderInYear, short Year)
	{
		//This will construct a date by date order in Year
		clsDate Date1 = GetDateFromDayOrderInYear(DateOrderInYear, Year);

		this->_Day = Date1.Day;
		this->_Month = Date1.Month;
		this->_Year = Date1.Year;
	}

	void SetDay(short Day)
	{
		this->_Day = Day;
	}

	short GetDay() const
	{
		return this->_Day;
	}

	__declspec(property(get = GetDay, put = SetDay)) short Day;

	void SetMonth(short Month)
	{
		this->_Month = Month;
	}

	short GetMonth() const
	{
		return this->_Month;
	}

	__declspec(property(get = GetMonth, put = SetMonth)) short Month;

	void SetYear(short Year)
	{
		this->_Year = Year;
	}

	short GetYear() const
	{
		return this->_Year;
	}

	__declspec(property(get = GetYear, put = SetYear)) short Year;

	short ReadDayInWeek()
	{
		std::string Input;
		std::cout << "Enter a day (between 1 and 7): ";
		std::cin >> Input;
		while (!IsValidDayInWeek(Input))
		{
			std::cout << "Enter a valid day (between 1 and 7): ";
			std::cin >> Input;
		}
		return std::stoi(Input);
	}

	short ReadDayInMonth()
	{
		std::string Input;
		std::cout << "Enter a day (between 1 and 31): ";
		std::cin >> Input;
		while (!IsValidDayInMonth(Input))
		{
			std::cout << "Enter a valid day (between 1 and 31): ";
			std::cin >> Input;
		}
		return std::stoi(Input);
	}

	short ReadMonth()
	{
		std::string Input;
		std::cout << "Enter a Month (between 1 and 12): ";
		std::cin >> Input;
		while (!IsValidMonth(Input))
		{
			std::cout << "Enter a valid Month (between 1 and 12): ";
			std::cin >> Input;
		}
		return std::stoi(Input);
	}

	short ReadYear()
	{
		std::string Input;
		std::cout << "Enter a Year (between 1000 and 9999): ";
		std::cin >> Input;
		while (!IsValidYear(Input))
		{
			std::cout << "Enter a valid Year (between 1000 and 9999): ";
			std::cin >> Input;
		}
		return std::stoi(Input);
	}

	static std::string ReadFullDateString(const std::string& Message, const std::string& ErrorMessage, std::string Delem)
	{
		std::string Input;
		std::cout << Message;
		std::cin >> Input;

		while (!IsValidDateFormat(Input, Delem))
		{
			std::cout << ErrorMessage;
			std::cin >> Input;
		}

		std::string Day = Input.substr(0, 2);
		std::string Month = Input.substr(3, 2);
		std::string Year = Input.substr(6, 4);

		if ((
			IsValidDayInMonth(Day) &&
			IsValidMonth(Month) &&
			IsValidYear(Year)) &&
			IsValidDate(std::stoi(Day), std::stoi(Month), std::stoi(Year)))
		{
			return Input;
		}

		return ReadFullDateString(Message, ErrorMessage, Delem);
	}

	clsDate ReadFullDate(clsDate Date)
	{
		do
		{
			Date.Day = (ReadDayInMonth());
			Date.Month = ReadMonth();
			Date.Year = ReadYear();
		} while (!(IsValidDate(Date)));

		return Date;
	}

	clsDate ReadFullDate()
	{
		return this->ReadFullDate(*this);
	}

	static bool IsFirstDayInMonth(clsDate Date)
	{
		return (Date.Day == 1);
	}

	static bool IsLastDayInMonth(clsDate Date)
	{
		return (Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year));
	}

	static bool IsFirstMonthInYear(short Month)
	{
		return Month == 1;
	}

	static bool IsLastMonthInYear(short Month)
	{
		return Month == 12;
	}

	static bool IsValidYear(const std::string& Year)
	{
		if (clsCheck::CheckLength(Year, 4) && !clsInputValidation::IsDigitOnly(Year)) return false;

		return (std::stoi(Year) >= 1000 && std::stoi(Year) <= 9999);
	}

	static bool IsValidMonth(const std::string& Month)
	{
		if (clsCheck::CheckLength(Month, 2) && !clsInputValidation::IsDigitOnly(Month)) return false;

		return (std::stoi(Month) >= 1 && std::stoi(Month) <= 12);
	}

	static bool IsValidDayInWeek(const std::string& Day)
	{
		if (clsCheck::CheckLength(Day, 1) && !clsInputValidation::IsDigitOnly(Day)) return false;

		return (std::stoi(Day) >= 1 && std::stoi(Day) <= 12);
	}

	static bool IsValidDayInMonth(const std::string& Day)
	{
		if (clsCheck::CheckLength(Day, 2) && !clsInputValidation::IsDigitOnly(Day)) return false;

		return (std::stoi(Day) >= 1 && std::stoi(Day) <= 31);
	}

	static bool IsValidDateFormat(const std::string& DateStr, std::string Delem)
	{
		// Check if the string length is correct
			// For DD<delim>MM<delim>YYYY, the length should be 10 + (Delem.length() - 1) * 2
		short expectedLength = 8 + Delem.length() * 2;
		if (DateStr.length() != expectedLength)
		{
			return false;
		}

		// Check if the separators match the delimiter
		if (DateStr.substr(2, Delem.length()) != Delem || DateStr.substr(5 + Delem.length() - 1, Delem.length()) != Delem)
		{
			return false;
		}

		// Check if all other characters are digits
		for (short i = 0; i < DateStr.length(); ++i)
		{
			// Skip the delimiter positions
			if (i == 2 || i == 5 + Delem.length() - 1)
				continue;

			// Check if the character is a digit
			if (!isdigit(DateStr[i]))
			{
				return false;
			}
		}

		return false;
	}

	static bool IsValidDate(short Day, short Month, short Year)
	{
		if (Day > NumberOfDaysInMonth(Month, Year))
		{
			std::cout << "\n=== enter a valid date ===\n"
				<< std::endl;
			return false;
		}
		return true;
	}

	static bool IsValidDate(clsDate Date)
	{
		if (Date.Day > NumberOfDaysInMonth(Date.Month, Date.Year))
		{
			std::cout << "\n=== enter a valid date ===\n"
				<< std::endl;
			return false;
		}
		return true;
	}

	bool IsValidDate()
	{
		this->IsValidDate(*this);
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year < Date2.Year)
			? true
			: ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return !IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year == Date2.Year)
			? ((Date1.Month == Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false)
			: false;
	}

	static Enum::DateCompare CompareDate(clsDate Date1, clsDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return Enum::DateCompare::BEFORE;

		if (IsDate1AfterDate2(Date1, Date2))
			return Enum::DateCompare::AFTER;

		return Enum::DateCompare::EQUAL;
	}

	static clsDate GetSystemDate()
	{
		time_t t = time(0);
		std::tm* now = localtime(&t);
		short Day, Month, Year;

		Day = (short)(now->tm_mday);
		Month = (short)(now->tm_mon + 1);
		Year = (short)(now->tm_year + 1900);

		return clsDate(Day, Month, Year);
	}

	static std::string GetSystemDateTimeString()
	{
		time_t t = time(0);
		std::tm* now = localtime(&t);
		short Day, Month, Year, Hour, Minute, Second;

		Year = (short)(now->tm_year + 1900);
		Month = (short)(now->tm_mon + 1);
		Day = (short)(now->tm_mday);
		Hour = (short)(now->tm_hour);
		Minute = (short)(now->tm_min);
		Second = (short)(now->tm_sec);


		return (
			std::to_string(Day) + "/" + std::to_string(Month) + "/" +
			std::to_string(Year) + " - " + std::to_string(Hour) + ":" +
			std::to_string(Minute) + ":" + std::to_string(Second)
			);
	}

	static short NumberOfDaysInYear(short Year)
	{
		return clsCheck::CheckLeapYear(Year) ? 366 : 365;
	}

	short NumberOfDaysInYear()
	{
		return this->NumberOfDaysInYear(this->Year);
	}

	static short NumberOfHoursInYear(short Year)
	{
		return NumberOfDaysInYear(Year) * static_cast<short>(Enum::DateType::HOUR);
	}

	short NumberOfHoursInYear()
	{
		return this->NumberOfHoursInYear(this->Year);
	}

	static short NumberOfMinutesInYear(short Year)
	{
		return NumberOfHoursInYear(Year) * static_cast<short>(Enum::DateType::MINUTE);
	}

	short NumberOfMinutesInYear()
	{
		return this->NumberOfMinutesInYear(this->Year);
	}

	static short NumberOfSecondsInYear(short Year)
	{
		return NumberOfMinutesInYear(Year) * static_cast<short>(Enum::DateType::SECOND);
	}

	short NumberOfSecondsInYear()
	{
		return this->NumberOfSecondsInYear(this->Year);
	}

	static short NumberOfDaysInMonth(short Month, short Year)
	{
		if (!clsInputValidation::IsNumberInRange(Month, 1, 12))
			return 0;

		short DaysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		return (Month == 2) ? (clsCheck::CheckLeapYear(Year) ? 29 : 28) : DaysInMonth[Month - 1];
	}

	short NumberOfDaysInMonth()
	{
		return this->NumberOfDaysInMonth(this->Month, this->Year);
	}

	static short NumberOfHoursInMonth(short Month, short Year)
	{
		return NumberOfDaysInMonth(Month, Year) * static_cast<short>(Enum::DateType::HOUR);
	}

	short NumberOfHoursInMonth() const
	{
		return NumberOfHoursInMonth(this->Month, this->Year);
	}

	static short NumberOfMinutesInMonth(short Month, short Year)
	{
		return NumberOfHoursInMonth(Month, Year) * static_cast<short>(Enum::DateType::MINUTE);
	}

	short NumberOfMinutesInMonth()
	{
		return this->NumberOfMinutesInMonth(this->Month, this->Year);
	}

	static short NumberOfSecondsInMonth(short Month, short Year)
	{
		return NumberOfMinutesInMonth(Month, Year) * static_cast<short>(Enum::DateType::SECOND);
	}

	short NumberOfSecondsInMonth()
	{
		return this->NumberOfSecondsInMonth(this->Month, this->Year);
	}

	static clsDate IncreaseDateByOneDay(clsDate& Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date.Month))
			{
				Date.Month = 1;
				Date.Day = 1;
				Date.Year++;
			}
			else
			{
				Date.Day = 1;
				Date.Month++;
			}
		}
		else
		{
			Date.Day++;
		}

		return Date;
	}

	clsDate IncreaseDateByOneDay()
	{
		return this->IncreaseDateByOneDay(*this);
	}

	static clsDate IncreaseDateByXDays(short Days, clsDate& Date)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}

		return Date;
	}

	clsDate IncreaseDateByXDays(short Days)
	{
		return IncreaseDateByXDays(Days, *this);
	}

	static clsDate IncreaseDateByOneWeek(clsDate& Date)
	{
		for (short i = 1; i <= 7; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}

	clsDate IncreaseDateByOneWeek()
	{
		return this->IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(short weeks, clsDate& Date)
	{
		for (short i = 1; i <= weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}

	clsDate IncreaseDateByXWeeks(short Weeks)
	{
		return this->IncreaseDateByXWeeks(Weeks, *this);
	}

	static clsDate IncreaseDateByOneMonth(clsDate& Date)
	{
		if (IsLastMonthInYear(Date.Month))
		{
			Date.Month = 1;
			Date.Year++;
		}
		else
			Date.Month++;

		short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Month, Date.Year);

		if (Date.Day > NumberOfDaysInCurrentMonth)
			Date.Day = NumberOfDaysInCurrentMonth;

		return Date;
	}

	clsDate IncreaseDateByOneMonth()
	{
		return this->IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonth(short months, clsDate& Date)
	{
		for (short i = 1; i <= months; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}

	clsDate IncreaseDateByXMonth(short Months)
	{
		return this->IncreaseDateByXMonth(Months, *this);
	}

	static clsDate IncreaseDateByOneYear(clsDate& Date)
	{
		Date.Year++;
		return Date;
	}

	clsDate IncreaseDateByOneYear()
	{
		return IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYear(short Years, clsDate& Date)
	{
		for (short i = 1; i <= Years; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}
		return Date;
	}

	clsDate IncreaseDateByXYear(short Years)
	{
		return this->IncreaseDateByXYear(Years, *this);
	}

	static clsDate IncreaseDateByXYearFaster(short Years, clsDate& Date)
	{
		Date.Year += Years;
		return Date;
	}

	clsDate IncreaseDateByXYearFaster(short Years)
	{
		return this->IncreaseDateByXYearFaster(Years, *this);
	}

	static clsDate IncreaseDateByOneDecade(clsDate& Date)
	{
		Date.Year += 10;
		return Date;
	}

	clsDate IncreaseDateByOneDecade()
	{
		return this->IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(short Decades, clsDate& Date)
	{
		for (short i = 1; i <= Decades; i++)
		{
			Date = IncreaseDateByOneDecade(Date);
		}
		return Date;
	}

	clsDate IncreaseDateByXDecades(short Decades)
	{
		return this->IncreaseDateByXDecades(Decades, *this);
	}

	static clsDate IncreaseDateByXDecadesFaster(short Decades, clsDate& Date)
	{
		Date.Year += (Decades * 10);
		return Date;
	}

	clsDate IncreaseDateByXDecadesFaster(short Decades)
	{
		return this->IncreaseDateByXDecadesFaster(Decades, *this);
	}

	static clsDate IncreaseDateByOneCentury(clsDate& Date)
	{
		Date.Year += 100;
		return Date;
	}

	clsDate IncreaseDateByOneCentury()
	{
		return this->IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate& Date)
	{
		Date.Year += 1000;
		return Date;
	}

	clsDate IncreaseDateByOneMillennium()
	{
		return this->IncreaseDateByOneMillennium(*this);
	}

	static clsDate DecreaseDateByOneDay(clsDate& Date)
	{
		if (IsFirstDayInMonth(Date))
		{
			if (IsFirstMonthInYear(Date.Month))
			{
				Date.Month = 12;
				Date.Day = 31;
				Date.Year--;
			}
			else
			{
				Date.Day = NumberOfDaysInMonth(Date.Month, Date.Year);
				Date.Month--;
			}
		}
		else
		{
			Date.Day--;
		}
		return Date;
	}

	clsDate DecreaseDateByOneDay()
	{
		return DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(short days, clsDate& Date)
	{
		for (short i = 1; i <= days; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	clsDate DecreaseDateByXDays(short Days)
	{
		return DecreaseDateByXDays(Days, *this);
	}

	static clsDate DecreaseDateByOneWeek(clsDate& Date)
	{
		for (short i = 1; i <= 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	clsDate DecreaseDateByOneWeek()
	{
		return this->DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(short weeks, clsDate& Date)
	{
		for (short i = 1; i <= weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}

	clsDate DecreaseDateByXWeeks(short Weeks)
	{
		return this->DecreaseDateByXWeeks(Weeks, *this);
	}

	static clsDate DecreaseDateByOneMonth(clsDate& Date)
	{
		if (IsFirstMonthInYear(Date.Month))
		{
			Date.Month = 12;
			Date.Year--;
		}
		else
			Date.Month--;

		short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Month, Date.Year);

		if (Date.Day > NumberOfDaysInCurrentMonth)
			Date.Day = NumberOfDaysInCurrentMonth;

		return Date;
	}

	clsDate DecreaseDateByOneMonth()
	{
		return this->DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonth(short Months, clsDate& Date)
	{
		for (short i = 1; i <= Months; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}

	clsDate DecreaseDateByXMonth(short Months)
	{
		return this->DecreaseDateByXMonth(Months, *this);
	}

	static clsDate DecreaseDateByOneYear(clsDate& Date)
	{
		Date.Year--;
		return Date;
	}

	clsDate DecreaseDateByOneYear()
	{
		return DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYear(short years, clsDate& Date)
	{
		for (short i = 1; i <= years; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}
		return Date;
	}

	clsDate DecreaseDateByXYear(short Years)
	{
		return this->DecreaseDateByXYear(Years, *this);
	}

	static clsDate DecreaseDateByXYearFaster(short years, clsDate& Date)
	{
		Date.Year -= years;
		return Date;
	}

	clsDate DecreaseDateByXYearFaster(short Years)
	{
		return this->DecreaseDateByXYearFaster(Years, *this);
	}

	static clsDate DecreaseDateByOneDecade(clsDate& Date)
	{
		Date.Year -= 10;
		return Date;
	}

	clsDate DecreaseDateByOneDecade()
	{
		return this->DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(short Decades, clsDate& Date)
	{
		for (short i = 1; i <= Decades; i++)
		{
			Date = DecreaseDateByOneDecade(Date);
		}
		return Date;
	}

	clsDate DecreaseDateByXDecades(short Decades)
	{
		return this->DecreaseDateByXDecades(Decades, *this);
	}

	static clsDate DecreaseDateByXDecadesFaster(short Decades, clsDate& Date)
	{
		Date.Year -= (Decades * 10);
		return Date;
	}

	clsDate DecreaseDateByXDecadesFaster(short Decades)
	{
		return this->DecreaseDateByXDecadesFaster(Decades, *this);
	}

	static clsDate DecreaseDateByOneCentury(clsDate& Date)
	{
		Date.Year -= 100;
		return Date;
	}

	clsDate DecreaseDateByOneCentury()
	{
		return this->DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate& Date)
	{
		Date.Year -= 1000;
		return Date;
	}

	clsDate DecreaseDateByOneMillennium()
	{
		return this->DecreaseDateByOneMillennium(*this);
	}

	static short DayOfWeekOrder(short day, short Month, short Year)
	{
		short A, Y, M;
		A = (14 - Month) / 12;
		Y = Year - A;
		M = Month + (12 * A) - 2;

		return (day + Y + (Y / 4) - (Y / 100) + (Y / 400) + ((31 * M) / 12)) % 7;
	}

	static short DayOfWeekOrder(clsDate Date)
	{
		return DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
	}

	short DayOfWeekOrder()
	{
		return this->DayOfWeekOrder(*this);
	}

	static std::string DayshortName(short DayOfWeekOrder)
	{
		std::string ArrDayNames[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

		return ArrDayNames[DayOfWeekOrder];
	}

	std::string DayshortName()
	{
		return this->DayshortName(this->Day);
	}

	static std::string MonthShortName(short MonthNumber)
	{
		std::string Months[12] = { "Jan", "Feb", "Mar",
								  "Apr", "May", "Jun",
								  "Jul", "Aug", "Sept",
								  "Oct", "Nov", "Dec" };
		return (Months[MonthNumber - 1]);
	}

	std::string MonthShortName()
	{
		return this->MonthShortName(this->Month);
	}

	static short NumberOfDaysFromBeginningOfTheYear(short Day, short Month, short Year)
	{
		short TotalDays = 0;
		for (short i = 1; i <= Month - 1; i++)
		{
			TotalDays += NumberOfDaysInMonth(i, Year);
		}
		return TotalDays += Day;
	}

	short NumberOfDaysFromBeginningOfTheYear()
	{
		return this->NumberOfDaysFromBeginningOfTheYear(this->Day, this->Month, this->Year);
	}

	static short GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEnfDay)
	{
		short days = 0;
		short swapFlag = 1;

		if (IsDate1EqualDate2(Date1, Date2))
			return IncludeEnfDay ? 1 : 0;

		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			SwapDate(Date1, Date2);
			swapFlag = -1;
		}

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			days++;
			Date1 = IncreaseDateByOneDay(Date1);
		}

		return IncludeEnfDay ? ++days * swapFlag : days * swapFlag;
	}

	short GetDifferenceInDays(clsDate Date2, bool IncludeEnfDay)
	{
		return this->GetDifferenceInDays(*this, Date2, IncludeEnfDay);
	}

	static clsDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
	{
		clsDate Date;
		short RemainingDays = DateOrderInYear;
		short MonthDays = 0;

		Date.Year = Year;
		Date.Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInMonth(Date.Month, Year);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}

		}
		return Date;
	}

	static void SwapDate(clsDate& Date1, clsDate& Date2)
	{
		clsDate TempDate;
		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;
	}

	clsDate DateAddDays(short Days)
	{
		short RemainingDays = Days + NumberOfDaysFromBeginningOfTheYear(Day, Month, Year);
		short MonthDays = 0;

		Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInMonth(Month, Year);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Month++;

				if (Month > 12)
				{
					Month = 1;
					Year++;

				}
			}
			else
			{
				Day = RemainingDays;
				break;
			}

		}
	}

	static std::string FormateDate(clsDate Date, std::string DateFormat)
	{
		std::string Day = std::to_string(Date.Day);
		std::string Month = std::to_string(Date.Month);
		std::string Year = std::to_string(Date.Year);

		DateFormat = clsString::ReplaceWordsInString(DateFormat, "dd", Day);
		DateFormat = clsString::ReplaceWordsInString(DateFormat, "mm", Month);
		DateFormat = clsString::ReplaceWordsInString(DateFormat, "yyyy", Year);

		return DateFormat;
	}

	std::string FormateDate(std::string DateFormat)
	{
		return this->FormateDate(*this, DateFormat);
	}

	static clsDate StringToDate(std::string DateSting, std::string Delem)
	{
		clsDate Date;
		std::vector<std::string> vDate;

		vDate = clsString::SplitString(DateSting, Delem);

		Date.Day = std::stoi(vDate[0]);
		Date.Month = std::stoi(vDate[1]);
		Date.Year = std::stoi(vDate[2]);

		return Date;
	}

	static std::string DateToString(clsDate Date, std::string Delem = "/")
	{
		return (std::to_string(Date.Day) + Delem + std::to_string(Date.Month) + Delem + std::to_string(Date.Year));
	}

	std::string DateToString(std::string Delem)
	{
		return this->DateToString(*this, Delem);
	}

	static void DisplayMonthCalendar(short Month, short Year)
	{
		short Current = DayOfWeekOrder(1, Month, Year);
		short NumberOfDays = NumberOfDaysInMonth(Month, Year);

		printf("\n ________________%s________________\n\n", MonthShortName(Month).c_str());

		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		short i;
		for (i = 0; i < Current; i++)
		{
			printf("     ");
		}

		for (short j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);
			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}

		printf("\n __________________________________\n");
	}

	void DisplayMonthCalendar()
	{
		this->DisplayMonthCalendar(this->Month, this->Year);
	}

	static void DisplayYearCalendar(short Year)
	{
		printf("\n __________________________________\n");
		printf("\tCalendar - %d", Year);
		printf("\n __________________________________\n");

		for (short i = 1; i < 12; i++)
		{
			DisplayMonthCalendar(i, Year);
		}
	}

	void DisplayYearCalendar()
	{
		this->DisplayYearCalendar(this->Year);
	}
};

