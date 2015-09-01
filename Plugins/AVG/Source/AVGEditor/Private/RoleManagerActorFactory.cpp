// Fill out your copyright notice in the Description page of Project Settings.

#include "AVGEditorPrivatePCH.h"
#include "RoleManager.h"
#include "RoleManagerActor.h"
#include "RoleManagerComponent.h"
#include "RoleManagerActorFactory.h"


URoleManagerActorFactory::URoleManagerActorFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DisplayName = NSLOCTEXT("Role", "RoleManagerFactoryDisplayName", "Add RoleManager");
	NewActorClass = ARoleManagerActor::StaticClass();
}

void URoleManagerActorFactory::PostSpawnActor(UObject* Asset, AActor* NewActor)
{
	if (URoleManager* Sprite = Cast<URoleManager>(Asset))
	{
		FActorLabelUtilities::SetActorLabelUnique(NewActor, Sprite->GetName());

		ARoleManagerActor* TypedActor = CastChecked<ARoleManagerActor>(NewActor);
		URoleManagerComponent* RenderComponent = TypedActor->GetRenderComponent();
		check(RenderComponent);

		RenderComponent->UnregisterComponent();
		RenderComponent->SetRoleManager(Sprite);


		RenderComponent->RegisterComponent();
	}
}

void URoleManagerActorFactory::PostCreateBlueprint(UObject* Asset, AActor* CDO)
{
	if (URoleManager* Sprite = Cast<URoleManager>(Asset))
	{
		if (ARoleManagerActor* TypedActor = Cast<ARoleManagerActor>(CDO))
		{
			URoleManagerComponent* RenderComponent = TypedActor->GetRenderComponent();
			check(RenderComponent);

			RenderComponent->SetRoleManager(Sprite);

// 			if (Sprite->BodySetup != nullptr)
// 			{
// 				RenderComponent->BodyInstance.CopyBodyInstancePropertiesFrom(&(Sprite->BodySetup->DefaultInstance));
// 			}
		}
	}
}

bool URoleManagerActorFactory::CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg)
{
	if (AssetData.IsValid() && AssetData.GetClass()->IsChildOf(URoleManager::StaticClass()))
	{
		return true;
	}
	else
	{
		OutErrorMsg = NSLOCTEXT("Role", "CanCreateActorFrom_NoRoleManager", "No RoleManager was specified.");
		return false;
	}
}
