// Fill out your copyright notice in the Description page of Project Settings.

#include "AVGEditorPrivatePCH.h"
#include "RoleFactory.h"

#define LOCTEXT_NAMESPACE "Role"

URoleFactory::URoleFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = URoleInfo::StaticClass();
}

UObject* URoleFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	URoleInfo* NewObjectAsset = ConstructObject<URoleInfo>(Class, InParent, Name, Flags | RF_Transactional);
	return NewObjectAsset;
}

#undef LOCTEXT_NAMESPACE
