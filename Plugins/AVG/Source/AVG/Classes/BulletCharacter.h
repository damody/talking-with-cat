// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperFlipbook.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "BulletCharacter.generated.h"

UENUM(BlueprintType)
enum class EBulletStausEnum : uint8
{
    Creating,
    Nothing,
	Flying1,
    Flying2,
    Deathing,
    ToBeKnocking,
    BeKnocking
};

/**
 *
 */
UCLASS()
class AVG_API ABulletCharacter : public ACharacter
{
    GENERATED_UCLASS_BODY()

    // Name of the Sprite component
    static FName SpriteComponentName;

public:
    virtual void PostInitializeComponents() override;

    UFUNCTION()
    void OnBeginAttackOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnEndAttackOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION()
    void OnBeginBodyOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnEndBodyOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    // Called every frame
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable, Category = "FightRole")
    void SetDestination(FVector dst);

    UFUNCTION(BlueprintCallable, Category = "FightRole")
    void InitData(float hp, float Velocity, int32 Faction, FVector Destination);

    /** Returns Sprite subobject **/
    FORCEINLINE class UPaperFlipbookComponent* GetSprite() const {
        return Sprite;
    }
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
    float   HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	float   Flying1Delay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
    float   BeKnockingDelay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
    float   DeathingDelay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
    float   ImpulseVelocity;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FightRole")
    float StateDeltaSeconds;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FightRole")
    TArray<AActor*> BodyCollision;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FightRole")
    TArray<AActor*> AttackCollision;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
    EBulletStausEnum FightStaus;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
    EBulletStausEnum AssignFightStaus;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
    FVector Destination;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
    int32 Faction;

    UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
    UBoxComponent * AttackBox;

    UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
    UBoxComponent * BodyBox;

    UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
    UPaperFlipbookComponent * Sprite;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
    UPaperFlipbook * PF_Flying1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
	UPaperFlipbook * PF_Flying2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
    UPaperFlipbook * PF_Deathing1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
    UPaperFlipbook * PF_BeKnocking1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightRole")
    float   Damage;

};
