// Fill out your copyright notice in the Description page of Project Settings.

#include "AVGPrivatePCH.h"
#include "BulletCharacter.h"
#include "PaperFlipbookComponent.h"
// for GEngine
#include "Engine.h"

FName ABulletCharacter::SpriteComponentName(TEXT("Sprite0"));

ABulletCharacter::ABulletCharacter(const FObjectInitializer& ObjectInitializer)
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
        static FName CollisionProfileName(TEXT("CharacterMesh"));
        Sprite->SetCollisionProfileName(CollisionProfileName);
        Sprite->bGenerateOverlapEvents = false;
    }
    if(AttackBox)
    {
        AttackBox->SetBoxExtent(FVector(10, 10, 10));
        AttackBox->OnComponentBeginOverlap.AddDynamic(this, &ABulletCharacter::OnBeginAttackOverlap);
        AttackBox->OnComponentEndOverlap.AddDynamic(this, &ABulletCharacter::OnEndAttackOverlap);
    }
    if(BodyBox)
    {
        BodyBox->SetBoxExtent(FVector(10, 10, 10));
        BodyBox->OnComponentBeginOverlap.AddDynamic(this, &ABulletCharacter::OnBeginBodyOverlap);
        BodyBox->OnComponentEndOverlap.AddDynamic(this, &ABulletCharacter::OnEndBodyOverlap);
    }
    FightStaus = EBulletStausEnum::Creating;
	AssignFightStaus = EBulletStausEnum::Nothing;
}

void ABulletCharacter::PostInitializeComponents()
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

void ABulletCharacter::OnBeginAttackOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(OtherActor != this)
    {
		AFightCharacter* tfc = dynamic_cast<AFightCharacter*>(OtherActor);
        if(tfc && tfc->Faction != this->Faction)
        {
            if(OtherComp->GetName() == TEXT("BodyBox0"))
            {
                AttackCollision.Add(OtherActor);
//                 GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, this->GetName() + TEXT(" OnBeginAttackOverlap"));
//                 GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, OtherActor->GetName() + " All: " + FString::FromInt(AttackCollision.Num()));
            }
        }
    }
}

void ABulletCharacter::OnEndAttackOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AFightCharacter* tfc = dynamic_cast<AFightCharacter*>(OtherActor);
    if(tfc && tfc->Faction != this->Faction)
    {
        if(OtherComp->GetName() == TEXT("BodyBox0"))
        {
            AttackCollision.Remove(OtherActor);
//             GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, this->GetName() + TEXT(" OnEndAttackOverlap"));
//             GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, OtherActor->GetName() + " All: " + FString::FromInt(AttackCollision.Num()));
        }
    }
}

void ABulletCharacter::OnBeginBodyOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(OtherActor != this)
    {
		AFightCharacter* tfc = dynamic_cast<AFightCharacter*>(OtherActor);
        if(tfc && tfc->Faction != this->Faction)
        {
            BodyCollision.Add(OtherActor);
//             GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, this->GetName() + TEXT(" OnBeginBodyOverlap"));
//             GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, OtherComp->GetName() + " All: " + FString::FromInt(BodyCollision.Num()));
        }
    }
}

void ABulletCharacter::OnEndBodyOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AFightCharacter* tfc = dynamic_cast<AFightCharacter*>(OtherActor);
    if(tfc && tfc->Faction != this->Faction)
    {
        BodyCollision.Remove(OtherActor);
//         GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, this->GetName() + TEXT(" OnEndBodyOverlap"));
//         GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, OtherComp->GetName() + " All: " + FString::FromInt(BodyCollision.Num()));
    }
}

void ABulletCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if((HP <= 0 && FightStaus != EBulletStausEnum::Deathing)
		|| (FightStaus != EBulletStausEnum::Creating && FVector::Dist(StartPosition, GetActorLocation()) > MaxDistance))
    {
        FightStaus = EBulletStausEnum::Deathing;
        Sprite->SetFlipbook(PF_Deathing1);
    }
	if (AssignFightStaus != EBulletStausEnum::Nothing 
		&& FightStaus != EBulletStausEnum::Deathing)
	{
		FightStaus = AssignFightStaus;
		AssignFightStaus = EBulletStausEnum::Nothing;
	}
    switch(FightStaus)
    {
    case EBulletStausEnum::Creating:
    {
        if(!CharacterMovement->IsFalling())
        {
            StateDeltaSeconds += DeltaSeconds;
        }
        if(StateDeltaSeconds > 0.2)
        {
			StartPosition = this->GetActorLocation();
            UNavigationSystem::SimpleMoveToLocation(this->GetController(), Destination);
            FightStaus = EBulletStausEnum::Flying1;
            Sprite->SetFlipbook(PF_Flying1);
            AttackCollision.Empty();
            StateDeltaSeconds = 0;
        }
    }
    break;
    case EBulletStausEnum::ToBeKnocking:
    {
        Sprite->SetFlipbook(PF_BeKnocking1);
        StateDeltaSeconds = 0;
        FightStaus = EBulletStausEnum::BeKnocking;
    }
    break;
    case EBulletStausEnum::BeKnocking:
    {
        StateDeltaSeconds += DeltaSeconds;
        if(StateDeltaSeconds > BeKnockingDelay)
        {
            if(HP > 0)
            {
				UNavigationSystem::SimpleMoveToLocation(this->GetController(), Destination);
				FightStaus = EBulletStausEnum::Flying1;
                Sprite->SetFlipbook(PF_Flying1);
            }
            StateDeltaSeconds = 0;
        }
    }
    break;
	case EBulletStausEnum::Flying1:
	{
		StateDeltaSeconds += DeltaSeconds;
		if (StateDeltaSeconds > DeathingDelay)
		{
			StateDeltaSeconds = 0;
			FightStaus = EBulletStausEnum::Flying2;
			Sprite->SetFlipbook(PF_Flying2);
		}
	}
	break;
    case EBulletStausEnum::Flying2:
    {
        StateDeltaSeconds += DeltaSeconds;
		// attack
		if (this->GetVelocity().IsNearlyZero(1))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, this->GetName() + TEXT(" attack"));
			Sprite->SetFlipbook(PF_Deathing1);
			this->GetController()->StopMovement();
			FightStaus = EBulletStausEnum::Deathing;
			StateDeltaSeconds = 0;
			break;
		}
		// attack
		if (AttackCollision.Num() > 0)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, this->GetName() + TEXT(" attack"));
			Sprite->SetFlipbook(PF_Deathing1);
			this->GetController()->StopMovement();
			FightStaus = EBulletStausEnum::Deathing;
			StateDeltaSeconds = 0;

			for (int32 i = 0; i < AttackCollision.Num(); ++i)
			{
				AFightCharacter* tfc = dynamic_cast<AFightCharacter*>(AttackCollision[i]);
				if (tfc)
				{
					tfc->HP -= Damage;
					// À»¯}
					//tfc->AssignFightStaus = EFightStausEnum::ToBeKnocking;
					// À»­¸
					FVector OurV;
					if (Faction == 0)
					{
						OurV = FVector(-1, 0, 0);
					}
					else
					{
						OurV = FVector(1, 0, 0);
					}
					tfc->GetCharacterMovement()->Velocity = OurV * ImpulseVelocity;
				}
			}
		}
    }
    break;
    case EBulletStausEnum::Deathing:
    {
        StateDeltaSeconds += DeltaSeconds;
        if(StateDeltaSeconds > DeathingDelay)
        {
            this->Destroy();
        }
    }
    break;
    }

    // if no attack go to Destination

}

void ABulletCharacter::SetDestination(FVector dst)
{
    Destination = dst;
}

void ABulletCharacter::InitData(float hp, float Velocity, int32 f, FVector d)
{
	HP = hp;
	ImpulseVelocity = Velocity;
	Faction = f;
	Destination = d;
}
