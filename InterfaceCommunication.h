#pragma once
#include <iostream>

class InterfaceCommunication
{
public:
	virtual void SendEmail(std::string Title, std::string Body) = 0;
	virtual void SendSMS(std::string TextMessage) = 0;
};

