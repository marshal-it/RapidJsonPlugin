#include "RapidJson.h"
#include "RapidJsonPCH.h"
#include "JsonNodeTool.h"

TArray<FString> JsonNodeTool::ConvertStringToArray(FString orgin, FString split)
{
	TArray<FString> SplitArray;
	FString TempOrgin = orgin;
	while (1)
	{
		FString Left, Right;
		if (UKismetStringLibrary::Split(TempOrgin, split, Left, Right, ESearchCase::IgnoreCase, ESearchDir::FromStart))
		{
			SplitArray.Add(Left);
			TempOrgin = Right;
		}
		else
		{
			SplitArray.Add(TempOrgin);
			break;
		}
	}
	return SplitArray;
}
