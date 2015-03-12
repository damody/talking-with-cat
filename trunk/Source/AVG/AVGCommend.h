// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AVGCommend.generated.h"


UENUM(BlueprintType)
enum class ETextEffectEnum : uint8
{
	InsideStory, //�¹�
	LightCurtain, //�}��
	Flash,	//�{��
	Wait,	//����
	AutomaticSAVE,	//�۰ʦs��
	Yen,		//�p�ϥ�
	Fonts,		//���ܦr��
	FontsSize,	//��r�j�p
	FontColor,	//��r�C��
	BGM			//�I������
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
