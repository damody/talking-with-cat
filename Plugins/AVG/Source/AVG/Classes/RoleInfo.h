// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "PaperSprite.h"
#include "RoleInfo.generated.h"

USTRUCT(BlueprintType, meta = (DisplayThumbnail = "true"))
struct FFace
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Role")
    FString Mood;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Role", meta = (DisplayThumbnail = "true"))
    UPaperSprite * Sprite;
};

/**
 *
 */
UCLASS(BlueprintType, meta = (DisplayThumbnail = "true"))
class AVG_API URoleInfo : public UObject
{
    GENERATED_BODY()
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Role")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Role", meta = (DisplayThumbnail = "true"))
    TArray<FFace> Faces;

	UPaperSprite* GetSprite()
    {
		UPaperSprite* SourceTexture = nullptr;
        if(Faces.Num() > 0)
        {
            SourceTexture = Faces[0].Sprite;
        }
        return SourceTexture;
    }

    UFUNCTION(BlueprintCallable, Category = "Role")
    UPaperSprite * GetNormalSprite();

    UFUNCTION(BlueprintCallable, Category = "Role")
    UPaperSprite * GetSpriteByMood(FString mood);

};
