// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Actor.h"
#include "ScriptBlueprint.h"
#include "StoryManager.generated.h"

UENUM(BlueprintType)
enum class EStoryReturnEnum : uint8
{
	Option1,
	Option2,
	Option3,
	NotYet
};

UCLASS()
class AVG_API AStoryManager : public AActor
{
	GENERATED_BODY()
	
public:	
	
	// Sets default values for this actor's properties
	AStoryManager();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Story")
	FString GetStoryMap();

	UFUNCTION(BlueprintCallable, Category = "Story")
	FString NextStory(int32 currentChoose);
		
	UFUNCTION(BlueprintCallable, Category = "Story", Meta = (ExpandEnumAsExecs = "Branches"))
	void PlayStory(int32 CurrentStep, int32& OutStep, EStoryReturnEnum& Branches);

	static void ConvertVarArrayToMap(TArray<FString> VarNames, TArray<float> VarValue, TMap<FString, float>& VarMap);

	static void ConvertVarMapToArray(const TMap<FString, float>& VarMap, TArray<FString>& VarNames, TArray<float>& VarValue);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Story")
	FString StoryName;

	FString LastStoryBranch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Story")
	FString StartStory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Story")
	FString StoredLastStoryBranch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Story")
	TArray<UScriptBlueprint*> StoryFiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Story")
	int32 CurrentChoose;

	TArray<int32> AlreadyChoose;
};
