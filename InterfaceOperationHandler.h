#pragma once
#include <vector>
#include <string>

template <class T>

class InterfaceOperationHandler
{
protected:
	virtual static T _ConvertLogLineToRecord(std::string Line, std::string Separator = "#//#") = 0;
	virtual static T _ConvertLineToObject(std::string Line, std::string Separator = "#//#") = 0;
	virtual static std::string _ConvertObjectToLine(T Object, std::string Separator = "#//#") = 0;
	virtual static std::vector<T> _LoadDataFromFile() = 0;
	virtual static void _SaveObjectsDataToFile(std::vector<T> vObjects) = 0;
	virtual static T _GetEmptyObject() = 0;
	virtual std::string _PrepareLogRecord(std::string Separator = "#//#") = 0;
	virtual void _AddDataLineToFile(std::string DataLine) = 0;
	virtual void _AddNew() = 0;
	virtual void _Update() = 0;
};

