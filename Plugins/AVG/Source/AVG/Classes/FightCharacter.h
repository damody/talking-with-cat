// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperFlipbook.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "FightCharacter.generated.h"

UENUM(BlueprintType)
enum class EFightStausEnum : uint8
{
	Walking,
	Attacking,
	AttackEnding
};

/**
 * 
 */
UCLASS()
class AVG_API AFightCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()
	
	// Name of the Sprite component
	static FName SpriteComponentName;

public:
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnBeginAttackOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnEndAttackOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnBeginBodyOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnEndBodyOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "FightRole")
	void SetDestination(FVector dst);

	/** Returns Sprite subobject **/
	FORCEINLINE class UPaperFlipbookComponent* GetSprite() const { return Sprite; }
public:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> BodyCollision;
	
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> AttackCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	EFightStausEnum FightStaus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	FVector Destination;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	int32 Faction;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* AttackBox;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BodyBox;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
	UPaperFlipbookComponent* Sprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	UPaperFlipbook* PF_Walking1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	UPaperFlipbook* PF_Attacking1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	UPaperFlipbook* PF_Walking2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	UPaperFlipbook* PF_Attacking2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	UPaperFlipbook* PF_Walking3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	UPaperFlipbook* PF_Attacking3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	int32	RoleLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	int32	Credit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	float	BasisHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	float	HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	float	BasisAttackDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	float	AttackDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	int32	AttackRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	int32	BasisAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	int32	Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	int32	BasisMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	int32	MoveSpeed;

};
