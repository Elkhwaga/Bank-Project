#pragma once
#include "clsDepositScreen.h"
#include "clsScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

class clsTransactionsMainScreen : protected clsScreen
{
private:
	enum enTransactionsMenuOptions
	{
		DEPOSIT = 1,
		WITHDRAW,
		SHOW_TOTAL_BALANCE,
		TRANSFER,
		TRANSFER_LOG,
		SHOW_MAIN_MENU
	};

	static enTransactionsMenuOptions _ReadTransactionsMenuOption()
	{
		std::cout << std::left << std::setw(37) << "" << "\tChoose what do you want to do? [1 to 6]\n";
		short _Choice = clsInputNumber::ReadNumberInRange("\tEnter number between 1 to 6: ", 1, 6, 37);
		return static_cast<enTransactionsMenuOptions>(_Choice);
	}

	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen()
	{
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalancesScreen()
	{
		clsTotalBalancesScreen::ShowTotalBalancesScreen();
	}

	static void _ShowTransferScreen()
	{
		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransferLogScreen()
	{
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _GoBackToTransactionsMenu()
	{
		clsUtils::Pause("\n\nPress any key to go back to transactions menu ...\n");
		ShowTransactionsMenu();
	}

	static void _PerfromTransactionsMenuOption(enTransactionsMenuOptions TransactionsMenuOption)
	{
		switch (TransactionsMenuOption)
		{
		case clsTransactionsMainScreen::DEPOSIT:
			clsUtils::ClearScreen();
			_ShowDepositScreen();
			_GoBackToTransactionsMenu();
			break;

		case clsTransactionsMainScreen::WITHDRAW:
			clsUtils::ClearScreen();
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenu();
			break;

		case clsTransactionsMainScreen::SHOW_TOTAL_BALANCE:
			clsUtils::ClearScreen();
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenu();
			break;

		case clsTransactionsMainScreen::TRANSFER:
			clsUtils::ClearScreen();
			_ShowTransferScreen();
			_GoBackToTransactionsMenu();
			break;

		case clsTransactionsMainScreen::TRANSFER_LOG:
			clsUtils::ClearScreen();
			_ShowTransferLogScreen();
			_GoBackToTransactionsMenu();
			break;

		case clsTransactionsMainScreen::SHOW_MAIN_MENU:
			break;
		}
	}

public:
	static void ShowTransactionsMenu()
	{
		if (!CheckAccessRights(clsUser::enPermissions::TRNASACTIONS)) return;

		clsUtils::ClearScreen();

		_DrawScreenHeader("\t     Transactions Screen");

		std::cout << std::left << std::setw(37) << "" << "\t=============================================\n";
		std::cout << std::left << std::setw(37) << "" << "\t\t\tTransactions Menu\n";
		std::cout << std::left << std::setw(37) << "" << "\t=============================================\n";
		std::cout << std::left << std::setw(37) << "" << "\t[1] Deposit.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[2] Withdraw.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[3] Total Balances.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[4] Transfer.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[5] Transfer Log.\n";
		std::cout << std::left << std::setw(37) << "" << "\t[6] Main Menu.\n";
		std::cout << std::left << std::setw(37) << "" << "\t=============================================\n" << std::endl;

		_PerfromTransactionsMenuOption(_ReadTransactionsMenuOption());
	}
};

