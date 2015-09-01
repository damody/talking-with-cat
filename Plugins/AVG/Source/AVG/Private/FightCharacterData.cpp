// Fill out your copyright notice in the Description page of Project Settings.

#include "AVGPrivatePCH.h"
#include "FightCharacterData.h"
#include "AssetRegistryModule.h"
#include "Misc/OutputDevice.h"


bool UFightCharacterData::SaveCharacter(APaperCharacter* data, FString outpath)
{
    FString name;
    data->GetName(name);
    FString PackageName = outpath;
    PackageName += name;
    UPackage* Package = CreatePackage(NULL, *PackageName);
	UFightCharacterData* NewAsset = NewObject<UFightCharacterData>(Package, FName("FightCharacterData"), RF_Public);
	NewAsset->pos = data->GetActorLocation();
	name = TEXT("FCD_") + name;
	NewAsset->Rename(*name);
    FAssetRegistryModule::AssetCreated(NewAsset);
    NewAsset->MarkPackageDirty();
    FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
    return UPackage::SavePackage(Package, data, RF_Public, *PackageFileName, GError, nullptr, false, true, SAVE_None);
}


bool UFightCharacterData::SaveCharacters_Array(TArray<APaperCharacter*> chars, FString outpath)
{
	bool res = true;
    for(int32 i = 0; i < chars.Num(); ++i)
    {
        APaperCharacter* data = chars[i];
        FString name;
        data->GetName(name);
        FString PackageName = outpath;
        PackageName += name;
		UPackage* Package = CreatePackage(NULL, *PackageName);
		UFightCharacterData* NewAsset = NewObject<UFightCharacterData>(Package, FName("FightCharacterData"), RF_Public);
		NewAsset->pos = data->GetActorLocation();
		name = TEXT("FCD_") + name;
		NewAsset->Rename(*name);
// 		FAssetRegistryModule::AssetCreated(NewAsset);
// 		NewAsset->MarkPackageDirty();
        FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
        res &= UPackage::SavePackage(Package, data, RF_Public, *PackageFileName, GError, nullptr, false, true, SAVE_None);
    }
	return res;
}
