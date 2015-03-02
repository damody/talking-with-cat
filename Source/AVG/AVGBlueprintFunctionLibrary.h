// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/EngineTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AVGBlueprintFunctionLibrary.generated.h"


/**
 * 
 */
UCLASS(BlueprintType)
class AVG_API UAVGBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Tools")
	static	TArray<FVector2D> Make2DposArray(int32 s1, int32 s2);
	
};
