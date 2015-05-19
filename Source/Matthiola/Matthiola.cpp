// Fill out your copyright notice in the Description page of Project Settings.

#include "Matthiola.h"
#include "RoleInfo.h"
#include "RoleInfoThumbnailRenderer.h"
#include "ThumbnailRendering/ThumbnailManager.h"

class FMyCodeProjectModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule()
	{
		UThumbnailManager::Get().RegisterCustomRenderer(URoleInfo::StaticClass(), URoleInfoThumbnailRenderer::StaticClass());
	}
	virtual void ShutdownModule()
	{
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE(FMyCodeProjectModule, Matthiola, "Matthiola");
