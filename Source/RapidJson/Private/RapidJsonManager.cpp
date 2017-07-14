#include "RapidJson.h"
#include "RapidJsonPCH.h"
#include "RapidJsonManager.h"
#include <utility>

#if PLATFORM_WINDOWS
#pragma optimize("",off) 
#endif

RapidJsonManager* RapidJsonManager::instance = nullptr;

RapidJsonManager::RapidJsonManager()
{
	init();
}

RapidJsonManager::~RapidJsonManager()
{
	std::map<JSON_TYPE_ENUM, Document*>::iterator It;
	for (It=m_JsonMap.begin();It!=m_JsonMap.end();It++)
	{
		Document* temp = It->second;
		delete temp;
		temp = 0;
	}
	m_JsonMap.clear();
}

FString RapidJsonManager::GetKeyValue(JSON_TYPE_ENUM Type, FString key, FString name)
{
	std::string _key = JsonNodeTool::toString(key);
	std::string _name = JsonNodeTool::toString(name);

	Document* doc = GetJsonDocBykKey(Type);

	rapidjson::Value &keyValue = (*doc)[_key.c_str()];
	rapidjson::Value &nameValue = keyValue[_name.c_str()];

	std::string tempValue = "no result!";
	tempValue = GetStringByType(nameValue);
	return JsonNodeTool::toFString(tempValue);
}

std::string RapidJsonManager::ArrayToString(rapidjson::Value& value)
{
	rapidjson::Value &ArrayValue = value;
	std::string tt;
	for (unsigned int i = 0; i < ArrayValue.Size(); i++)
	{
		std::string temp;
		temp = GetStringByType(ArrayValue[i]);
		tt.append(temp);
		if (i < ArrayValue.Size() - 1)
		{
			tt.append("|");
		}
	}
	return tt;
}

void RapidJsonManager::init()
{
	std::string initJsonPath = JsonPathRoot + "tables.json";
	if (!checkFileExist(initJsonPath))
	{
		return;
	}
	char* jsonContent = ReadJsonFile(initJsonPath.c_str());

	size_t len = strlen(jsonContent);

	char* buffer = new char[len + 1];

	memcpy(buffer, jsonContent, len*sizeof(char)); //sizeof(char)  != sizeof(char*)

	Document ResDoc;

	if (ResDoc.ParseInsitu(jsonContent).HasParseError())
	{
		return;
	}
	//parsing to document succeeded
//	assert(ResDoc.IsObject());
	assert(ResDoc.IsArray());
	char* jsontemp;
	for (unsigned int i =0; i < ResDoc.Size(); i++)
	{
		rapidjson::Value &v = ResDoc[i];

		std::string key;
		key = v[0].GetString();
		std::string res;
		res = v[1].GetString();

		//if (ResDoc.HasMember(key.c_str()))
		//{
		//	res = ResDoc[key.c_str()].GetString();
		assert(JsonPathRoot);
		std::string temppath = JsonPathRoot + res;
		jsontemp = ReadJsonFile(temppath.c_str());
		Document* TempDoc = new Document();
		if (TempDoc->ParseInsitu(jsontemp).HasParseError())
		{
			continue;
		}
		m_JsonMap.insert(make_pair(JSON_TYPE_ENUM(atoi(key.c_str())), TempDoc));
	}
//	GetJsonDocBykKey(JSON_TYPE_ENUM::JSON_TYPE_RESOURCE);
}

bool RapidJsonManager::checkFileExist(const std::string XmlPath)
{
	return true;
}


Document* RapidJsonManager::GetJsonDocBykKey(JSON_TYPE_ENUM KeyEnum)
{
	Document* doc = m_JsonMap[KeyEnum];

	//{} 是对象，对象通过Value["key"].GetString取值，[]是数组，可以用通过Value["ptr"].GetString()下标取值
	//if (doc)
	//{
	//	assert(doc->IsObject());
	//	rapidjson::Value &a = (*doc)[tempkey_t.c_str()];
	//	assert(a.IsObject());
	//	rapidjson::Value &b = a["anger_max"]; //150 --直接通过Value去取值
	//	int ts = b.GetInt();
	//	UE_LOG(LogClass, Log, TEXT("this is a value. %d"), ts);
	//	std::string tt;
	//	int te = 0;
	//	for (Value::ConstMemberIterator itr = a.MemberBegin(); itr != a.MemberEnd(); ++itr)
	//	{
	//		tt.append(itr->name.GetString());
	//		tt.append("-:-");
	//		te = itr->value.GetInt(); //15 通过遍历迭代取值
	//	}
	//}
	return doc;
}

std::string RapidJsonManager::GetStringByType(rapidjson::Value& value)
{
	std::string Content;
	rapidjson::Type type = value.GetType();
	switch (type)
	{
	case rapidjson::kNullType:
		Content = "";
		break;
	case rapidjson::kFalseType:
	case rapidjson::kTrueType:
		Content = JsonNodeTool::toString(value.GetBool());
		break;
	case rapidjson::kObjectType:
		break;
	case rapidjson::kArrayType:
		Content = ArrayToString(value);
		break;
	case rapidjson::kStringType:
		Content = value.GetString();
		break;
	case rapidjson::kNumberType:
	{
		if (value.IsInt())
		{
			Content = JsonNodeTool::toString(value.GetInt());
		}
		if (value.IsDouble())
		{
			Content = JsonNodeTool::toString(value.GetDouble());
		}
		break;
	}
	default:
		Content = "no content type find!";
		break;
	}
	return Content;
}

char* RapidJsonManager::ReadJsonFile(const char* filePath)
{
		FILE *fp;
		char *content = NULL;
		int count = 0;
		if (filePath != NULL)
		{
			//打开文件
			fopen_s(&fp, filePath, "r");
			if (fp != NULL)
			{
				fseek(fp, 0, SEEK_END);
				count = ftell(fp);
				rewind(fp);
				if (count > 0)
				{
					content = (char*)malloc(sizeof(char)*(count + 1));
					count = fread(content, sizeof(char), count, fp);
					content[count] = '\0';
				}
				fclose(fp);
			}
		}
		return content;
}

#if PLATFORM_WINDOWS
#pragma optimize("",on) 
#endif