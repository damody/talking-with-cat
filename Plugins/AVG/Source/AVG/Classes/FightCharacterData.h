// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "PaperCharacter.h"
#include "FightCharacterData.generated.h"

/**
 * 
 */
UCLASS()
class AVG_API UFightCharacterData : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AssetData")
	FVector pos;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SaveCharacter (PaperCharacter)"), Category = "AssetData")
	static bool SaveCharacter(APaperCharacter* chars, FString outpath);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SaveCharacters (PaperCharacter array)"), Category = "AssetData")
	static bool SaveCharacters_Array(TArray<APaperCharacter*> chars, FString outpath);
		
};
