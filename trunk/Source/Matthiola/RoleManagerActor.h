// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RoleInfo.h"
#include "RoleManagerActor.generated.h"

UCLASS(ClassGroup = Role)
class MATTHIOLA_API ARoleManagerActor : public AActor
{
	GENERATED_UCLASS_BODY()
	
private:
	UPROPERTY(Category = Role, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Role,Rendering,Physics,Components|Role", AllowPrivateAccess = "true"))
	class URoleManagerComponent* RenderComponent;
public:

	// AActor interface
#if WITH_EDITOR
	virtual bool GetReferencedContentObjects(TArray<UObject*>& Objects) const override;
#endif
	// End of AActor interface

	/** Returns RenderComponent subobject **/
	FORCEINLINE class URoleManagerComponent* GetRenderComponent() const { return RenderComponent; }
};
