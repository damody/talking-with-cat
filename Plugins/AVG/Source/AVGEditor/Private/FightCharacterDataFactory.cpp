// Fill out your copyright notice in the Description page of Project Settings.

#include "AVGEditorPrivatePCH.h"
#include "FightCharacterDataFactory.h"

#define LOCTEXT_NAMESPACE "Role"

UFightCharacterDataFactory::UFightCharacterDataFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UFightCharacterData::StaticClass();
}

UObject* UFightCharacterDataFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UFightCharacterData* NewObjectAsset = ConstructObject<UFightCharacterData>(Class, InParent, Name, Flags | RF_Transactional);
	return NewObjectAsset;
}

#undef LOCTEXT_NAMESPACE
