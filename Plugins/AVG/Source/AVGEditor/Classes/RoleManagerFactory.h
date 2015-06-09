// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealEd.h"
#include "Factories/Factory.h"
#include "RoleManager.h"
#include "RoleManagerFactory.generated.h"

/**
 * 
 */
UCLASS()
class AVGEDITOR_API URoleManagerFactory : public UFactory
{
	GENERATED_UCLASS_BODY()
	
	
	// UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	// End of UFactory interface
	
};
