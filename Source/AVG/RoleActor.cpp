// Fill out your copyright notice in the Description page of Project Settings.

#include "AVG.h"
#include "RoleActor.h"
#include <cmath>


UPaperSprite* ARoleActor::GetNormalSprite()
{
	if (FaceSprites.Num() > 0)
	{
		return FaceSprites[rand() % FaceSprites.Num()];
	}
	return nullptr;
}
