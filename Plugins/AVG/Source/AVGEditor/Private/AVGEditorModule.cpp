
#include "AVGEditorPrivatePCH.h"
#include "RoleInfo.h"
#include "RoleInfoThumbnailRenderer.h"
#include "ThumbnailRendering/ThumbnailManager.h"

DEFINE_LOG_CATEGORY(AVGEditor);


class FAVGEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		// Register the thumbnail renderers
		UThumbnailManager::Get().RegisterCustomRenderer(URoleInfo::StaticClass(), URoleInfoThumbnailRenderer::StaticClass());
	}

	virtual void ShutdownModule() override
	{
		if (UObjectInitialized())
		{
			// Unregister the thumbnail renderers
			UThumbnailManager::Get().UnregisterCustomRenderer(URoleInfo::StaticClass());
		}
	}
private:
};

IMPLEMENT_MODULE(FAVGEditorModule, AVGEditor);
