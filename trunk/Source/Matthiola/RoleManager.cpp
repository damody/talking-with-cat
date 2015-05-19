// Fill out your copyright notice in the Description page of Project Settings.

#include "Matthiola.h"
#include "RoleManager.h"


URoleInfo* URoleManager::GetRoleByName(FString name)
{
	for (int32 i = 0; i < Roles.Num(); ++i)
	{
		if (Roles[i]->Name == name)
		{
			return Roles[i];
		}
	}
	return nullptr;
}

