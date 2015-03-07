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

TArray<FString> UAVGBlueprintFunctionLibrary::SplitCheaper(FString longString)
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
			text = longString.Mid(last, i - last + 1);
			res.Add(text);
			last = i;
			nextline = 0;
		}
	}
	return res;
}

