// Fill out your copyright notice in the Description page of Project Settings.

#include "Matthiola.h"
#include "RoleInfo.h"
#include <random>

static std::default_random_engine generator;

UPaperSprite* URoleInfo::GetNormalSprite()
{
    if(Faces.Num() == 0)
    {
        return nullptr;
    }
    std::uniform_int_distribution<int> distribution(0, Faces.Num() - 1);
    return Faces[distribution(generator)].Sprite;
}

UPaperSprite* URoleInfo::GetSpriteByMood(FString mood)
{
    for(int32 i = 0; i < Faces.Num(); ++i)
    {
		if (Faces[i].Mood == mood)
		{
			return Faces[i].Sprite;
		}
    }
	return nullptr;
}
