// Fill out your copyright notice in the Description page of Project Settings.

#include "AVG.h"
#include "TextPage.h"

void UTextPage::ResetFadeIn()
{
	FadeInTextPos = 0;
}

FString UTextPage::GetFadeInText(bool& showAll)
{
	FadeInTextPos++;
	if (FadeInTextPos >= ShowText.Len())
	{
		showAll = true;
	}
	else
	{
		showAll = false;
	}
	return ShowText.Left(FadeInTextPos);
}
