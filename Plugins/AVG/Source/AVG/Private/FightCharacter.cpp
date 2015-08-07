// Fill out your copyright notice in the Description page of Project Settings.

#include "AVGPrivatePCH.h"
#include "FightCharacter.h"
#include "PaperFlipbookComponent.h"
// for GEngine
#include "Engine.h"

FName AFightCharacter::SpriteComponentName(TEXT("Sprite0"));

AFightCharacter::AFightCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.DoNotCreateDefaultSubobject(ACharacter::MeshComponentName))
{
	// Try to create the sprite component
	Sprite = ObjectInitializer.CreateOptionalDefaultSubobject<UPaperFlipbookComponent>(this, APaperCharacter::SpriteComponentName);
	AttackBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("AttackBox0"));
	BodyBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BodyBox0"));
	if (Sprite)
	{
		Sprite->AlwaysLoadOnClient = true;
		Sprite->AlwaysLoadOnServer = true;
		Sprite->bOwnerNoSee = false;
		Sprite->bAffectDynamicIndirectLighting = true;
		Sprite->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		Sprite->AttachParent = GetCapsuleComponent();
		static FName CollisionProfileName(TEXT("CharacterMesh"));
		Sprite->SetCollisionProfileName(CollisionProfileName);
		Sprite->bGenerateOverlapEvents = false;
	}
	if (AttackBox)
	{
		AttackBox->OnComponentBeginOverlap.AddDynamic(this, &AFightCharacter::OnBeginAttackOverlap);
		AttackBox->OnComponentEndOverlap.AddDynamic(this, &AFightCharacter::OnEndAttackOverlap);
	}
	if (BodyBox)
	{
		BodyBox->OnComponentBeginOverlap.AddDynamic(this, &AFightCharacter::OnBeginBodyOverlap);
		BodyBox->OnComponentEndOverlap.AddDynamic(this, &AFightCharacter::OnEndBodyOverlap);
	}
}

void AFightCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (!IsPendingKill())
	{
		if (Sprite)
		{
			// force animation tick after movement component updates
			if (Sprite->PrimaryComponentTick.bCanEverTick && GetCharacterMovement())
			{
				Sprite->PrimaryComponentTick.AddPrerequisite(GetCharacterMovement(), GetCharacterMovement()->PrimaryComponentTick);
			}
		}
	}
}

void AFightCharacter::OnBeginAttackOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AttackCollision.Add(OtherActor);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, this->GetName() + TEXT(" OnBeginAttackOverlap"));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, OtherActor->GetName() + " All: " + FString::FromInt(AttackCollision.Num()));
	
}

void AFightCharacter::OnEndAttackOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AttackCollision.Remove(OtherActor);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, this->GetName() + TEXT(" OnEndAttackOverlap"));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, OtherActor->GetName() + " All: " + FString::FromInt(AttackCollision.Num()));
}

void AFightCharacter::OnBeginBodyOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	BodyCollision.Add(OtherActor);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, this->GetName() + TEXT(" OnBeginBodyOverlap"));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, OtherActor->GetName() + " All: " + FString::FromInt(BodyCollision.Num()));
}

void AFightCharacter::OnEndBodyOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	BodyCollision.Remove(OtherActor);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, this->GetName() + TEXT(" OnEndBodyOverlap"));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, OtherActor->GetName() + " All: " + FString::FromInt(BodyCollision.Num()));
}

void AFightCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	bool needattack = false;
	// for loop all AFightCharacter
	for (TActorIterator<AFightCharacter> It(GetWorld()); It; ++It)
	{
		// if different Faction with our
		if (It->Faction != this->Faction)
		{
			// attack
			if (FVector::Dist(It->GetActorLocation(), this->GetActorLocation()) < AttackRadius)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, this->GetName() + TEXT(" attack"));
				Sprite->SetFlipbook(PF_Attacking1);
				this->GetController()->StopMovement();
				needattack = true;
				break;
			}
		}
	}
	if (!needattack)
	{
		//UNavigationSystem::SimpleMoveToLocation(this->GetController(), Destination);
	}
	// if no attack go to Destination
	
}

void AFightCharacter::SetDestination(FVector dst)
{
	Destination = dst;
}
