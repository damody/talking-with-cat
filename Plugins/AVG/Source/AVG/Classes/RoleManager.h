// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RoleInfo.h"
#include "RoleManager.generated.h"

UCLASS()
class AVG_API URoleManager : public UObject
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Role")
	FString ManagerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Role", meta = (DisplayThumbnail = "true"))
	TArray<URoleInfo*> Roles;

	UFUNCTION(BlueprintCallable, Category = "Role")
	URoleInfo* GetRoleByName(FString name);

	
};
