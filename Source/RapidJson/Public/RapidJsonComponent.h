// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "RapidJsonManager.h"
#include "RapidJsonComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RAPIDJSON_API URapidJsonComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URapidJsonComponent();

	//JSON_TYPE_ENUM
	UFUNCTION(BlueprintCallable, Category = "RapidJson")
	void SetJsonTypeEnum(JSON_TYPE_ENUM Enum);

	//{"key"{"name":"value"}}
	UFUNCTION(BlueprintCallable, Category = "RapidJson")
	FString GetValue(FString key, FString name);

	UFUNCTION(BlueprintPure, Category = "RapidJson")
	TArray<FString> SplitToString(FString origin, FString split);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	JSON_TYPE_ENUM CurrentJsonType = JSON_TYPE_ENUM::JSON_TYPE_NONE;
	
};
