// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AVGCommend.generated.h"


UENUM(BlueprintType)
enum class ETextEffectEnum : uint8
{
	InsideStory, //黑幕
	LightCurtain, //開幕
	Flash,	//閃光
	Wait,	//等待
	AutomaticSAVE,	//自動存檔
	Yen,		//小圖示
	Fonts,		//改變字型
	FontsSize,	//改字大小
	FontColor,	//改字顏色
	BGM			//背景音樂
};

UCLASS()
class AVG_API UAVGCommend : public UObject
{
	GENERATED_BODY()
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Page")
	ETextEffectEnum EffectId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Page")
	float Parmeter1;
};
