#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"

class clsTransferLogScreen : protected clsScreen
{
private:
	static void _PrintTransferLogRecordLine(clsBankClient::stTransferLogRecord TransferLogRecord)
	{
		std::cout << "| " << std::left << std::setw(25) << TransferLogRecord.DateTime;
		std::cout << "| " << std::left << std::setw(20) << TransferLogRecord.SourceAccountNumber;
		std::cout << "| " << std::left << std::setw(20) << TransferLogRecord.DestinationAccountNumber;
		std::cout << "| " << std::left << std::setw(15) << TransferLogRecord.Amount;
		std::cout << "| " << std::left << std::setw(20) << TransferLogRecord.SourceBalanceAfter;
		std::cout << "| " << std::left << std::setw(20) << TransferLogRecord.DestinationBalanceAfter;
		std::cout << "| " << std::left << std::setw(15) << TransferLogRecord.UserName;
		std::cout << "|";
	}

public:
	static void ShowTransferLogScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::TRANSFER_LOG)) return;

		std::vector<clsBankClient::stTransferLogRecord> vTransferLogRecord = clsBankClient::GetTransferLogList();

		std::string Title = "\tTransfer Log List Screen";
		std::string SubTitle = "\t\t(" + std::to_string(vTransferLogRecord.size()) + ") Transfer(s)";

		_DrawScreenHeader(Title, SubTitle);

		std::cout << "\n______________________________________________________________________________________________________________________________________________________\n";
		std::cout << "| " << std::left << std::setw(25) << "Date Time";
		std::cout << "| " << std::left << std::setw(20) << "S.Account Number";
		std::cout << "| " << std::left << std::setw(20) << "D.Account Number";
		std::cout << "| " << std::left << std::setw(15) << "Amount";
		std::cout << "| " << std::left << std::setw(20) << "S.Balance After";
		std::cout << "| " << std::left << std::setw(20) << "D.Balance After";
		std::cout << "| " << std::left << std::setw(15) << "User Name";
		std::cout << "|";
		std::cout << "\n______________________________________________________________________________________________________________________________________________________\n";

		if (vTransferLogRecord.size() == 0)

			std::cout << "\t\t\t   No transfers available in the system!\n";
		else
		{
			for (clsBankClient::stTransferLogRecord TransferLogRecord : vTransferLogRecord)
			{
				_PrintTransferLogRecordLine(TransferLogRecord);
				std::cout << std::endl;
			}
		}
		std::cout << "______________________________________________________________________________________________________________________________________________________\n" << std::endl;
	}
};

