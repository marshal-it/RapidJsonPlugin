#pragma once
/*
* Json数据定义
*/

UENUM(BlueprintType)
enum class JSON_TYPE_ENUM : uint8
{
	JSON_TYPE_NONE = 0,
	//"资源",访问resource.xml请使用std::string Factory::getResourcePath(resourceId);
	JSON_TYPE_RESOURCE = 1,
	//场景配置
	JSON_TYPE_SCENE = 2,
	//游戏配置
	JSON_TYPE_GAME = 3,
};