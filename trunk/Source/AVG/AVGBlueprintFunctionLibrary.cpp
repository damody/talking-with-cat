// Fill out your copyright notice in the Description page of Project Settings.

#include "AVG.h"
#include "AVGBlueprintFunctionLibrary.h"
// for GEngine
#include "Engine.h"


TArray<FVector2D> UAVGBlueprintFunctionLibrary::Make2DposArray(int32 s1, int32 s2)
{
	TArray<FVector2D> res;
	for (int i = 0; i < s1; ++i)
	{
		for (int j = 0; j < s2; ++j)
		{
			res.Add(FVector2D(i, j));
		}
	}
	return res;
}

TArray<FString> UAVGBlueprintFunctionLibrary::SplitCheaper3line(FString longString)
{
	TArray<FString> res;
	int nextline = 0;
	int last = 0;
	for (int i = 0; i < longString.Len(); ++i)
	{
		TCHAR n = longString[i];
		if (n == '\n')
		{
			nextline++;
		}
		if (nextline >= 3 || i == longString.Len() - 1)
		{
			FString text;
			text = longString.Mid(last + 1, i - last);
			res.Add(text);
			last = i;
			nextline = 0;
		}
	}
	return res;
}

TArray<UTextPage*> UAVGBlueprintFunctionLibrary::SplitCheaper(FString longString)
{
	TArray<UTextPage*> res;
	int nextline = 0;
	int last = -1;
	for (int i = 3; i < longString.Len(); ++i)
	{
		TCHAR n = longString[i];
		// 連續換行等於空一行
		if (longString[i-2] == '\n' && longString[i-1] == '\r' && longString[i] == '\n')
		{
			nextline++;
		}
		if (nextline > 0 || i == longString.Len() - 1)
		{
			UTextPage* tmp = NewObject<UTextPage>();
			tmp->HasCommend = false;
			tmp->Effect = NewObject<UAVGCommend>();
			FString text;
			text = longString.Mid(last + 1, i - last-1);
			tmp->ShowText = text;
			int32 findchr = 0;
			if (text[0] == L'《')
			{
				tmp->Effect = NewObject<UAVGCommend>();
				FString commend = text.Mid(1, text.Len() - 5);
				commend = commend.ToLower();
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, commend);
				if (commend == "inside story")
				{
					tmp->HasCommend = true;
					tmp->Effect->EffectId = ETextEffectEnum::InsideStory;
				}
				else if (commend == "light curtain")
				{
					tmp->HasCommend = true;
					tmp->Effect->EffectId = ETextEffectEnum::LightCurtain;
				}
				else if (commend.Left(4) == "wait")
				{
					tmp->HasCommend = true;
					tmp->Effect->EffectId = ETextEffectEnum::Wait;
					char* str = TCHAR_TO_ANSI(*commend);
					float time = 0;
					sscanf(str, "wait(%f)", &time);
					tmp->Effect->Parmeter1 = time;
				}
				else if (commend.Left(12) == "screen flash")
				{
					tmp->HasCommend = true;
					tmp->Effect->EffectId = ETextEffectEnum::Flash;
					char* str = TCHAR_TO_ANSI(*commend);
					float time = 0;
					sscanf(str, "screen flash(%f)", &time);
					tmp->Effect->Parmeter1 = time;
				}
				else if (commend.Left(3) == "bgm")
				{

				}
			}
			else if (text.FindChar(L'：', findchr))
			{
				tmp->ShowName = text.Left(findchr);
				tmp->ShowText = text.Mid(findchr + 1);
			}
			// 註解
			if (text[0] != L'#')
			{
				res.Push(tmp);
			}
			last = i;
			nextline = 0;
		}
	}	
	return res;
}
