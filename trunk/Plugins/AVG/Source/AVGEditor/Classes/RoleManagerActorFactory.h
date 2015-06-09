// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealEd.h"
#include "Factories/Factory.h"
#include "RoleManager.h"
#include "RoleManagerActorFactory.generated.h"

/**
 * 
 */
UCLASS()
class AVGEDITOR_API URoleManagerActorFactory : public UActorFactory
{
	GENERATED_UCLASS_BODY()
public:
// Begin UActorFactory Interface
	virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;
	virtual void PostCreateBlueprint(UObject* Asset, AActor* CDO) override;
	virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;
	// End UActorFactory Interface
};
