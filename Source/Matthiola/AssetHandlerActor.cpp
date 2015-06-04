// Fill out your copyright notice in the Description page of Project Settings.

#include "Matthiola.h"
#include "AssetHandlerActor.h"
#include "AssetRegistryModule.h"
#include "Misc/OutputDevice.h"
#include "FileHelpers.h"
#include "FightCharacterData.h"
#include "PaperCharacter.h"



// Sets default values
AAssetHandlerActor::AAssetHandlerActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AAssetHandlerActor::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AAssetHandlerActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

TArray<UObject*> AAssetHandlerActor::LoadObjectFormAssetByPath(FString path)
{
    TArray<UObject*> res;
    EngineUtils::FindOrLoadAssetsByPath(path, res, EngineUtils::ATL_Regular);

    return res;
}

bool AAssetHandlerActor::SaveObjectToAsset(UObject* data, FString outpath)
{
    FString name;
    data->GetName(name);
    FString PackageName = outpath;
    PackageName += name;
    UPackage* Package = CreatePackage(NULL, *PackageName);
    UObject* NewAsset = DuplicateObject(data, Package);
    FAssetRegistryModule::AssetCreated(NewAsset);
    NewAsset->Rename(*name);
    NewAsset->MarkPackageDirty();
    FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
    return UPackage::SavePackage(Package, data, RF_Public, *PackageFileName, GError, nullptr, false, true, SAVE_None);
}


bool AAssetHandlerActor::LoadCharacters_Array(TSubclassOf<class APaperCharacter> parentClass, FString path)
{
    UWorld* const World = GetWorld();
    if(World)
    {
        TArray<UObject*> datas;
        EngineUtils::FindOrLoadAssetsByPath(path, datas, EngineUtils::ATL_Regular);
        for(int32 i = 0; i < datas.Num(); ++i)
        {
            UFightCharacterData* ufcdata = Cast<UFightCharacterData>(datas[i]);
            APaperCharacter* newactor = World->SpawnActor<APaperCharacter>(parentClass);
            if(newactor != nullptr)
            {
                newactor->SetActorLocation(ufcdata->pos);
            }
        }
        return true;
    }
    return false;
}
