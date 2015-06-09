// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperFlipbook.h"
#include "PaperCharacter.h"
#include "FightCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AVG_API AFightCharacter : public APaperCharacter
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	UPaperFlipbook*	PF_Walking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	UPaperFlipbook*	PF_Attacking;

	float WalkingDuration();
	
	
};
