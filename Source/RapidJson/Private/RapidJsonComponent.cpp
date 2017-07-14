// Fill out your copyright notice in the Description page of Project Settings.

#include "RapidJson.h"
#include "RapidJsonComponent.h"


// Sets default values for this component's properties
URapidJsonComponent::URapidJsonComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void URapidJsonComponent::SetJsonTypeEnum(JSON_TYPE_ENUM Enum)
{
	CurrentJsonType = Enum;
}

FString URapidJsonComponent::GetValue(FString key, FString name)
{
	//默认是一层结构{ { } }
	return RapidJsonManager::Instance()->GetKeyValue(CurrentJsonType, key, name);
}

TArray<FString> URapidJsonComponent::SplitToString(FString origin, FString split)
{
	return JsonNodeTool::ConvertStringToArray(origin, split);
}

// Called when the game starts
void URapidJsonComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


void URapidJsonComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (RapidJsonManager::Instance() != nullptr)
	{
		RapidJsonManager::Instance()->empty();
	}
}

// Called every frame
void URapidJsonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

