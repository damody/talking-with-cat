// Fill out your copyright notice in the Description page of Project Settings.

#include "Matthiola.h"
#include "FightCharacter.h"


float AFightCharacter::WalkingDuration()
{
	if (PF_Walking != nullptr)
	{
		return PF_Walking->GetTotalDuration();
	}
	return 0;
}
