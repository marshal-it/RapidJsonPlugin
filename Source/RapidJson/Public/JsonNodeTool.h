#pragma once
#include <string>
#include <sstream>
using namespace std;

class JsonNodeTool
{
public:
	static std::string toString(int value)
	{
		std::ostringstream oss;
		oss << value;
		return oss.str();
	}

	static FString toFString(std::string value)
	{
		FString ConString(value.c_str());
		return ConString;
	}

	static std::string toString(FString value)
	{
		std::string ConString(TCHAR_TO_UTF8(*value));
		return ConString;
	}

	static std::string toString(bool value)
	{
		//std::ostringstream oss;
		//oss << value;
		//return oss.str();
		if (value)
		{
			return "true";
		}
		return "false";
	}

	static std::string toString(double value)
	{
		std::ostringstream oss;
		oss << value;
		return oss.str();
	}

	static TArray<FString> ConvertStringToArray(FString orgin, FString split);
};