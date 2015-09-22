// Fill out your copyright notice in the Description page of Project Settings.

#include "AVGPrivatePCH.h"
#include "StoryManager.h"

// Sets default values
AStoryManager::AStoryManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AStoryManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStoryManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

FString AStoryManager::NextStory(int32 currentChoose)
{
	if (StoredLastStoryBranch.Len() == 0)
	{
		StoredLastStoryBranch = TEXT("0");
		return StartStory;
	}
	CurrentChoose = currentChoose;
	LastStoryBranch = StoredLastStoryBranch;
	return GetStoryMap();
}

void AStoryManager::PlayStory(int32 CurrentStep, int32& OutStep, EStoryReturnEnum& Branches)
{
	OutStep = CurrentStep;
	OutStep++;
	if (CurrentStep == LastStoryBranch.Len())
	{
		StoredLastStoryBranch += FString::FromInt(CurrentChoose);
		switch (CurrentChoose)
		{
		case 1:
			Branches = EStoryReturnEnum::Option1;
			break;
		case 2:
			Branches = EStoryReturnEnum::Option2;
			break;
		case 3:
			Branches = EStoryReturnEnum::Option3;
			break;
		default:
			Branches = EStoryReturnEnum::NotYet;
			break;
		}
	}
	else if (CurrentStep > LastStoryBranch.Len())
	{
		Branches = EStoryReturnEnum::NotYet;
	}
	else
	{
		int32 branch = FCString::Atoi(*LastStoryBranch.Mid(CurrentStep, 1));
		switch (branch)
		{
		case 1:
			Branches = EStoryReturnEnum::Option1;
			break;
		case 2:
			Branches = EStoryReturnEnum::Option2;
			break;
		case 3:
			Branches = EStoryReturnEnum::Option3;
			break;
		default:
			Branches = EStoryReturnEnum::NotYet;
			break;
		}
	}
}

void AStoryManager::ConvertVarArrayToMap(TArray<FString> VarNames, TArray<float> VarValue, TMap<FString, float>& VarMap)
{
	for (int32 i = 0; i < VarNames.Num(); ++i)
	{
		VarMap.Add(VarNames[i], VarValue[i]);
	}
}

void AStoryManager::ConvertVarMapToArray(const TMap<FString, float>& VarMap, TArray<FString>& VarNames, TArray<float>& VarValue)
{
	VarMap.GenerateKeyArray(VarNames);
	VarMap.GenerateValueArray(VarValue);
}

