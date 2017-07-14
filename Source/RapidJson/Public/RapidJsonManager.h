#pragma once
#include <map>
#include <string>
#include <vector>
#include "JsonNodeTool.h"
#include "JsonDataDefine.h"

#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON

using namespace rapidjson;
using namespace std;

class RapidJsonManager
{
public:

	static RapidJsonManager* Instance()
	{
		if (instance == nullptr)
		{
			instance = new RapidJsonManager();
		}
		return instance;
	}

	void empty() 
	{
		delete instance;
		instance = nullptr;
	}

	//上面传输表类型，key名，name名，   ----------content类型
	FString GetKeyValue(JSON_TYPE_ENUM Type, FString key, FString name);

private:
	FString DirPath = FPaths::GameDir() + "Plugins/" + "RapidJson" + "/"; //----"SaveGame/Plugins/TIXmlToolKit/"
	FString ResPath = DirPath + "Resources/";
	const std::string JsonPathRoot = TCHAR_TO_UTF8(*ResPath);;

	std::map<JSON_TYPE_ENUM, Document*>  m_JsonMap;

	void init();
	bool checkFileExist(const std::string XmlPath);

	char* ReadJsonFile(const char* filePath);

	std::string ArrayToString(rapidjson::Value& value);

	Document* GetJsonDocBykKey(JSON_TYPE_ENUM KeyEnum);

	std::string GetStringByType(rapidjson::Value& value);

	std::string tempkey_t = "1";

	static RapidJsonManager* instance;

	RapidJsonManager();
	~RapidJsonManager();
};