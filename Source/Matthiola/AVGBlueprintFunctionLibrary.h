// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/EngineTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TextPage.h"
#include "AVGBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MATTHIOLA_API UAVGBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Tools")
	static	TArray<FVector2D> Make2DposArray(int32 size1, int32 size2);

	UFUNCTION(BlueprintCallable, Category = "Tools")
	static	TArray<FString> SplitCheaper3line(FString longString);

	UFUNCTION(BlueprintCallable, Category = "Tools")
	static	TArray<UTextPage*> SplitCheaper(FString longString);

	UFUNCTION(BlueprintCallable, Category = "Tools")
	static	bool MusicStringCmp(FString s1, FString s2);
};
