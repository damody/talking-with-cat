// Fill out your copyright notice in the Description page of Project Settings.

#include "Matthiola.h"
#include "RoleManagerFactory.h"

URoleManagerFactory::URoleManagerFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = URoleManager::StaticClass();
}

UObject* URoleManagerFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	URoleManager* NewObjectAsset = ConstructObject<URoleManager>(Class, InParent, Name, Flags | RF_Transactional);
	return NewObjectAsset;
}

