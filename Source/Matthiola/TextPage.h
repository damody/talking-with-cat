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
class MATTHIOLA_API UTextPage : public UObject
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category = "Page")
	void ResetFadeIn();

	UFUNCTION(BlueprintCallable, Category = "Page")
	FString GetFadeInText(bool& showAll);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Page")
	int32 FadeInTextPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Page")
	FString ShowName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Page")
	FString ShowText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Page")
	bool HasCommend;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Page")
	UAVGCommend* Effect;
};
