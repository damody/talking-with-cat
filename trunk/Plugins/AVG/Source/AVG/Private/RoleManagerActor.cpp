// Fill out your copyright notice in the Description page of Project Settings.

#include "AVGPrivatePCH.h"
#include "Engine.h"
#include "RoleManagerActor.h"
#include "RoleManager.h"
#include "RoleManagerComponent.h"


ARoleManagerActor::ARoleManagerActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	RenderComponent = ObjectInitializer.CreateDefaultSubobject<URoleManagerComponent>(this, TEXT("RenderComponent"));
	RenderComponent->Mobility = EComponentMobility::Static;

	RootComponent = RenderComponent;
}

#if WITH_EDITOR
bool ARoleManagerActor::GetReferencedContentObjects(TArray<UObject*>& Objects) const
{
	Super::GetReferencedContentObjects(Objects);
	
	if (URoleManager* SourceSprite = RenderComponent->GetRoleManager())
	{
		Objects.Add(SourceSprite);
	}
	return true;
}
#endif
