// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSprite.h"
#include "GameFramework/Actor.h"
#include "RoleActor.generated.h"



UENUM(BlueprintType)
enum class ERoleFaceEnum : uint8
{
	Normal,
	Laugh,
	Angry,
	Sadden,
	Cry,
	Shock
};


UCLASS(BlueprintType)
class AVG_API ARoleActor : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Role")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Role")
	TArray<UPaperSprite*> FaceSprites;

	UFUNCTION(BlueprintCallable, Category = "Role")
	UPaperSprite* GetNormalSprite();
};

