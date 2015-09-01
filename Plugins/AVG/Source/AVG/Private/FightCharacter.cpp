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
	
    if(Sprite)
    {
        Sprite->AlwaysLoadOnClient = true;
        Sprite->AlwaysLoadOnServer = true;
        Sprite->bOwnerNoSee = false;
        Sprite->bAffectDynamicIndirectLighting = true;
        Sprite->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		Sprite->AttachParent = GetCapsuleComponent();
		static FName CollisionProfileName(TEXT("Pawn"));
        Sprite->SetCollisionProfileName(CollisionProfileName);
        Sprite->bGenerateOverlapEvents = false;
    }
    if(AttackBox)
    {
		AttackBox->AttachParent = GetCapsuleComponent();
        AttackBox->SetBoxExtent(FVector(10, 10, 10));
        AttackBox->OnComponentBeginOverlap.AddDynamic(this, &AFightCharacter::OnBeginAttackOverlap);
        AttackBox->OnComponentEndOverlap.AddDynamic(this, &AFightCharacter::OnEndAttackOverlap);
		AttackBox->SetCollisionObjectType(ECC_Pawn);
		AttackBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		AttackBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Ignore);
		AttackBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
		AttackBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		AttackBox->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
		AttackBox->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Ignore);
		AttackBox->SetCollisionResponseToChannel(ECC_Destructible, ECR_Ignore);
		AttackBox->bGenerateOverlapEvents = true;
    }
    if(BodyBox)
    {
		BodyBox->AttachParent = GetCapsuleComponent();
        BodyBox->SetBoxExtent(FVector(10, 10, 10));
        BodyBox->OnComponentBeginOverlap.AddDynamic(this, &AFightCharacter::OnBeginBodyOverlap);
        BodyBox->OnComponentEndOverlap.AddDynamic(this, &AFightCharacter::OnEndBodyOverlap);
		BodyBox->SetCollisionObjectType(ECC_Pawn);
		BodyBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		BodyBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Ignore);
		BodyBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
		BodyBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		BodyBox->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
		BodyBox->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Ignore);
		BodyBox->SetCollisionResponseToChannel(ECC_Destructible, ECR_Ignore);
		BodyBox->bGenerateOverlapEvents = true;
    }
    FightStaus = EFightStausEnum::Creating;
    AssignFightStaus = EFightStausEnum::Nothing;
}

void AFightCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    if(!IsPendingKill())
    {
        if(Sprite)
        {
            // force animation tick after movement component updates
            if(Sprite->PrimaryComponentTick.bCanEverTick && GetCharacterMovement())
            {
                Sprite->PrimaryComponentTick.AddPrerequisite(GetCharacterMovement(), GetCharacterMovement()->PrimaryComponentTick);
            }
        }
    }
}

void AFightCharacter::OnBeginAttackOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(OtherActor != this)
    {
        AFightCharacter* tfc = dynamic_cast<AFightCharacter*>(OtherActor);
        if(tfc && tfc->Faction != this->Faction)
        {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, OtherActor->GetName() + OtherComp->GetName() + " All: " + FString::FromInt(AttackCollision.Num()));
            if(OtherComp->GetName() == TEXT("BodyBox0"))
            {
                AttackCollision.Add(OtherActor);
                GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, this->GetName() + TEXT(" OnBeginAttackOverlap"));
                
            }
        }
    }
}

void AFightCharacter::OnEndAttackOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    AFightCharacter* tfc = dynamic_cast<AFightCharacter*>(OtherActor);
    if(tfc && tfc->Faction != this->Faction)
    {
		
        if(OtherComp->GetName() == TEXT("BodyBox0"))
        {
            AttackCollision.Remove(OtherActor);
            GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, this->GetName() + TEXT(" OnEndAttackOverlap"));
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, OtherActor->GetName() + " All: " + FString::FromInt(AttackCollision.Num()));
        }
    }
}

void AFightCharacter::OnBeginBodyOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(OtherActor != this)
    {
        AFightCharacter* tfc = dynamic_cast<AFightCharacter*>(OtherActor);
        if(tfc && tfc->Faction != this->Faction)
        {
            //BodyCollision.Add(OtherActor);
//             GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, this->GetName() + TEXT(" OnBeginBodyOverlap"));
//             GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, OtherComp->GetName() + " All: " + FString::FromInt(BodyCollision.Num()));
        }
    }
}

void AFightCharacter::OnEndBodyOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    AFightCharacter* tfc = dynamic_cast<AFightCharacter*>(OtherActor);
    if(tfc && tfc->Faction != this->Faction)
    {
        //BodyCollision.Remove(OtherActor);
//         GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, this->GetName() + TEXT(" OnEndBodyOverlap"));
//         GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, OtherComp->GetName() + " All: " + FString::FromInt(BodyCollision.Num()));
    }
}

void AFightCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if(HP <= 0 && FightStaus != EFightStausEnum::Deathing)
    {
        FightStaus = EFightStausEnum::Deathing;
        Sprite->SetFlipbook(PF_Deathing1);
		this->GetController()->StopMovement();
        DeathingEvent(this);
    }
    if(AssignFightStaus != EFightStausEnum::Nothing
            && FightStaus != EFightStausEnum::Attacking
            && FightStaus != EFightStausEnum::Deathing)
    {
        FightStaus = AssignFightStaus;
        AssignFightStaus = EFightStausEnum::Nothing;
    }
    switch(FightStaus)
    {
    case EFightStausEnum::Creating:
    {
        if(!CharacterMovement->IsFalling())
        {
            StateDeltaSeconds += DeltaSeconds;
        }
        if(StateDeltaSeconds > 0.5)
        {
            UNavigationSystem::SimpleMoveToLocation(this->GetController(), Destination);
            FightStaus = EFightStausEnum::Walking;
            Sprite->SetFlipbook(PF_Walking1);
            AttackCollision.Empty();
            StateDeltaSeconds = 0;
            WalkingEvent(this);
        }
    }
    break;
    case EFightStausEnum::ToBeKnocking:
    {
        Sprite->SetFlipbook(PF_BeKnocking1);
		this->GetController()->StopMovement();
        StateDeltaSeconds = 0;
        FightStaus = EFightStausEnum::BeKnocking;
    }
    break;
    case EFightStausEnum::BeKnocking:
    {
        StateDeltaSeconds += DeltaSeconds;
        if(StateDeltaSeconds > BeKnockingDelay)
        {
            if(AttackCollision.Num() > 0)
            {
                FightStaus = EFightStausEnum::Attacking;
                Sprite->SetFlipbook(PF_Attacking1);
                AttackingEvent(this);
            }
            else
            {
                UNavigationSystem::SimpleMoveToLocation(this->GetController(), Destination);
                FightStaus = EFightStausEnum::Walking;
                Sprite->SetFlipbook(PF_Walking1);
                WalkingEvent(this);
            }
            StateDeltaSeconds = 0;
        }
    }
    break;
    case EFightStausEnum::Walking:
    {
        StateDeltaSeconds += DeltaSeconds;
		// attack
		if (AttackCollision.Num() > 0)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, this->GetName() + TEXT(" attack"));
			Sprite->SetFlipbook(PF_Attacking1);
			this->GetController()->StopMovement();
			FightStaus = EFightStausEnum::Attacking;
			StateDeltaSeconds = 0;
			break;
		}
        // sometime forget walking
        if(StateDeltaSeconds > 3 && this->GetVelocity().IsNearlyZero(1))
        {
            UNavigationSystem::SimpleMoveToLocation(this->GetController(), Destination);
        }
    }
    break;
    case EFightStausEnum::Attacking:
    {
        StateDeltaSeconds += DeltaSeconds;
        if(StateDeltaSeconds > AttackDelay)
        {
            for(int32 i = 0; i < AttackCollision.Num(); ++i)
            {
                AFightCharacter* tfc = dynamic_cast<AFightCharacter*>(AttackCollision[i]);
                if(tfc && tfc->Faction != this->Faction)
                {
                    tfc->HP -= Attack;
                    // À»¯}
                    if(FMath::FRandRange(0, 1) < KnockingProbability) 
					{
                        tfc->AssignFightStaus = EFightStausEnum::ToBeKnocking;
						// À»­¸
						FVector OurV = Destination - this->GetActorLocation();
						OurV.Normalize();
						tfc->GetCharacterMovement()->Velocity = OurV * KnockingVelocity;
                    }
                }
				else
				{
					AttackCollision.RemoveAt(i);
					i--;
				}
            }
            StateDeltaSeconds = 0;
            FightStaus = EFightStausEnum::AttackEnding;
            Sprite->SetFlipbook(PF_AttackEnding1);
            AttackEndingEvent(this);
        }
    }
    break;
    case EFightStausEnum::AttackEnding:
    {
        StateDeltaSeconds += DeltaSeconds;
        if(StateDeltaSeconds > AttackEndingDelay)
        {
            if(AttackCollision.Num() > 0)
            {
                FightStaus = EFightStausEnum::Attacking;
                Sprite->SetFlipbook(PF_Attacking1);
                AttackingEvent(this);
            }
            else
            {
                UNavigationSystem::SimpleMoveToLocation(this->GetController(), Destination);
                FightStaus = EFightStausEnum::Walking;
                Sprite->SetFlipbook(PF_Walking1);
                WalkingEvent(this);
            }
            StateDeltaSeconds = 0;
        }
    }
    break;
    case EFightStausEnum::Deathing:
    {
        StateDeltaSeconds += DeltaSeconds;
        if(StateDeltaSeconds > DeathingDelay)
        {
            this->Destroy();
        }
    }
    break;
    }

}

void AFightCharacter::SetFaceBack()
{
	Sprite->SetRelativeScale3D(FVector(-1, 1, 1));
	FVector arl = AttackBox->RelativeLocation;
	arl.X = -arl.X;
	AttackBox->SetRelativeLocation(arl);
	FVector brl = BodyBox->RelativeLocation;
	brl.X = -brl.X;
	BodyBox->SetRelativeLocation(brl);
}

void AFightCharacter::SetDestination(FVector dst)
{
    Destination = dst;
}
