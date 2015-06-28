// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EnumAsByte.h"
#include "MyActor.generated.h"

UENUM(BlueprintType)
enum class EMyEnum : uint8
{
	BranchA,
	BranchB
};

UCLASS()
class MATTHIOLA_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YourCategory")
	TArray<int32> Structs;

	UFUNCTION(BlueprintCallable, Category = "Stuff", Meta = (ExpandEnumAsExecs = "Branches"))
	void DoSomeBranch(int32 SomeInput, EMyEnum& Branches);
	
	UFUNCTION(BlueprintCallable, Category = "Stuff", Meta = (ExpandEnumAsExecs = "Branches"))
	int32 DoSomeBranch2(int32 SomeInput, EMyEnum& Branches);
};
