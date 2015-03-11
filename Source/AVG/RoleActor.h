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


UCLASS()
class AVG_API ARoleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoleActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Role")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Role")
	TArray<UPaperSprite*> Sprite;
};
