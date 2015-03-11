// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "TextPage.generated.h"


UENUM(BlueprintType)
enum class ETextEffectEnum : uint8
{
	Flash,
	Wait,
	AutomaticSAVE,
	Yen,
	Fonts,
	FontsSize,

};

/**
 * 
 */
UCLASS(BlueprintType)
class AVG_API UTextPage : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Page")
	FString ShowText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Page")
	ETextEffectEnum Effect;
};
