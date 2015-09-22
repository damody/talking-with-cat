// Fill out your copyright notice in the Description page of Project Settings.

#include "Matthiola.h"
#include "AVGBlueprintFunctionLibrary.h"
// for GEngine
#include "Engine.h"
#include "Runtime/MoviePlayer/Public/MoviePlayer.h"
#include "ContentStreaming.h"

TArray<FVector2D> UAVGBlueprintFunctionLibrary::Make2DposArray(int32 s1, int32 s2)
{
    TArray<FVector2D> res;
    for(int i = 0; i < s1; ++i)
    {
        for(int j = 0; j < s2; ++j)
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
    for(int i = 0; i < longString.Len(); ++i)
    {
        TCHAR n = longString[i];
        if(n == '\n')
        {
            nextline++;
        }
        if(nextline >= 3 || i == longString.Len() - 1)
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
    for(int i = 3; i < longString.Len(); ++i)
    {
        TCHAR n = longString[i];
        // 連續換行等於空一行
        if(longString[i - 2] == '\n' && longString[i - 1] == '\r' && longString[i] == '\n')
        {
            nextline++;
        }
        if(nextline > 0 || i == longString.Len() - 1)
        {
            UTextPage* tmp = NewObject<UTextPage>();
            tmp->HasCommend = false;
            tmp->Effect = NewObject<UAVGCommend>();
            FString text;
            text = longString.Mid(last + 1, i - last - 1);
            tmp->ShowText = text;
            int32 findchr = 0;
            // 《
            if(text[0] == L'\u300A')
            {
                tmp->Effect = NewObject<UAVGCommend>();
                FString commend = text.Mid(1, text.Len());
                commend = commend.ToLower();
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, commend);
                if(commend == "inside story")
                {
                    tmp->HasCommend = true;
                    tmp->Effect->EffectId = ETextEffectEnum::InsideStory;
                }
                else if(commend == "light curtain")
                {
                    tmp->HasCommend = true;
                    tmp->Effect->EffectId = ETextEffectEnum::LightCurtain;
                }
                else if(commend.Left(6) == "choose")
                {
                    tmp->HasCommend = true;
                    tmp->Effect->EffectId = ETextEffectEnum::Choose;
                    int32 dquotes[6];
                    commend.FindChar(L'\"', dquotes[0]);
                    for(int i = 1; i < 6; ++i)
                    {
                        FString strtmp = commend.Mid(dquotes[i - 1] + 1);
                        strtmp.FindChar(L'\"', dquotes[i]);
                        dquotes[i] += dquotes[i - 1] + 1;
                    }
                    FString choose1 = commend.Mid(dquotes[0] + 1, dquotes[1] - dquotes[0] - 1);
                    FString choose2 = commend.Mid(dquotes[2] + 1, dquotes[3] - dquotes[2] - 1);
                    FString choose3 = commend.Mid(dquotes[4] + 1, dquotes[5] - dquotes[4] - 1);
                    tmp->Effect->ChooseParmeter1 = choose1;
                    tmp->Effect->ChooseParmeter2 = choose2;
                    tmp->Effect->ChooseParmeter3 = choose3;
                }
                else if(commend.Left(4) == "wait")
                {
                    tmp->HasCommend = true;
                    tmp->Effect->EffectId = ETextEffectEnum::Wait;
                    char* str = TCHAR_TO_ANSI(*commend);
                    float time = 0;
                    sscanf(str, "wait(%f)", &time);
                    tmp->Effect->Parmeter1 = time;
                }
                else if(commend.Left(12) == "screen flash")
                {
                    tmp->HasCommend = true;
                    tmp->Effect->EffectId = ETextEffectEnum::Flash;
                    char* str = TCHAR_TO_ANSI(*commend);
                    float time = 0;
                    sscanf(str, "screen flash(%f)", &time);
                    tmp->Effect->Parmeter1 = time;
                }
                else if(commend.Left(3) == "bgm")
                {
                    tmp->HasCommend = true;
                    tmp->Effect->EffectId = ETextEffectEnum::BGM;
                    float time = 0;
                    int32 dquotes1;
                    commend.FindChar(L'\"', dquotes1);
                    int32 dquotes2;
                    commend.FindLastChar(L'\"', dquotes2);
                    FString midtext = commend.Mid(dquotes1 + 1, dquotes2 - dquotes1 - 1);
                    commend = commend.Mid(dquotes2 + 1);
                    char* str = TCHAR_TO_ANSI(*commend);
                    sscanf(str, "%f", &time);
                    tmp->Effect->Parmeter1 = time;
                    tmp->Effect->Parmeter2 = midtext;
                }
            }
            // ：
            else if(text.FindChar(L'\uFF1A', findchr))
            {
                tmp->ShowName = text.Left(findchr);
                tmp->ShowText = text.Mid(findchr + 1);
            }
            // 註解
            if(text[0] != '#')
            {
                res.Push(tmp);
            }
            last = i;
            nextline = 0;
        }
    }
    return res;
}

bool UAVGBlueprintFunctionLibrary::MusicStringCmp(FString s1, FString s2)
{
    int32 l1 = s1.Len();
    int32 l2 = s2.Len();
    if(l1 > l2)
    {
        l1 = l2;
    }
    GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, "l1: " + FString::FromInt(l1));
    bool cmp = true;
    for(int32 i = 0; i < l1; ++i)
    {
        if(s1[i] != s2[i])
        {
            cmp = false;
            break;
        }
    }
    GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, "s1: " + s1);
    GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, "s2: " + s2);
    if(cmp)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, "True");
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, "False");
    }
    return cmp;
}

bool UAVGBlueprintFunctionLibrary::MakeProgressLoadLevel()
{
    IStreamingManager::Get().StreamAllResources(10.0f);
    FLoadingScreenAttributes LoadingScreen;
    LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
    LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget(); // <-- test screen that comes with UE
    //LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
    //LoadingScreen.bMoviesAreSkippable = true;
    //LoadingScreen.MoviePaths.Add(TEXT("ggg"));
    GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
    GetMoviePlayer()->PlayMovie();
    return true;
}
