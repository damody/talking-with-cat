// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "AVGCommend.h"
#include "TextPage.generated.h"



/**
 * 
 */
UCLASS(BlueprintType)
class AVG_API UTextPage : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Page")
	FString ShowName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Page")
	FString ShowText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Page")
	bool HasCommend;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Page")
	UAVGCommend* Effect;
};
