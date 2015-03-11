// Fill out your copyright notice in the Description page of Project Settings.

#include "AVG.h"
#include "AVGBlueprintFunctionLibrary.h"

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
	int last = 0;
	for (int i = 3; i < longString.Len(); ++i)
	{
		TCHAR n = longString[i];
		if (longString[i-2] == '\n' && longString[i-1] == '\r' && longString[i] == '\n')
		{
			nextline++;
		}
		if (nextline > 0 || i == longString.Len() - 1)
		{
			UTextPage* tmp = NewObject<UTextPage>();
			FString text;
			text = longString.Mid(last + 1, i - last-1);
			tmp->ShowText = text;
			res.Push(tmp);
			last = i;
			nextline = 0;
		}
	}	
	return res;
}
