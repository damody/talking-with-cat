// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealEd.h"
#include "Factories/Factory.h"
#include "RoleInfo.h"
#include "RoleFactory.generated.h"

/**
 * 
 */
UCLASS()
class AVGEDITOR_API URoleFactory : public UFactory
{
	GENERATED_UCLASS_BODY()
	
	
	// UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	// End of UFactory interface
	
};
