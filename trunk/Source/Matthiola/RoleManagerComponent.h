// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Components/ShapeComponent.h"
#include "RoleManagerComponent.generated.h"

/**
 * A component that handles rendering and collision for a single instance of a UPaperSprite asset.
 *
 * This component is created when you drag a sprite asset from the content browser into a Blueprint, or
 * contained inside of the actor created when you drag one into the level.
 *
 * @see UPrimitiveComponent, UPaperSprite
 */

UCLASS(ShowCategories=(Mobility), ClassGroup=Role, meta=(BlueprintSpawnableComponent))
class MATTHIOLA_API URoleManagerComponent : public UShapeComponent
{
	GENERATED_UCLASS_BODY()

protected:
	// The sprite asset used by this component
	UPROPERTY(Category = Role, EditAnywhere, BlueprintReadOnly)
	URoleManager* SourceSprite;


public:
	/** Change the PaperSprite used by this instance. */
	UFUNCTION(BlueprintCallable, Category="Role")
	virtual bool SetRoleManager(class URoleManager* NewSprite);

	/** Gets the PaperSprite used by this instance. */
	UFUNCTION(BlueprintPure, Category="Role")
	virtual URoleManager* GetRoleManager();

protected:
	/** The extents of the box **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, export, Category=Shape)
	FVector BoxExtent;

public:
	/** 
	 * Change the box extent size. This is the unscaled size, before component scale is applied.
	 * @param	InBoxExtent: new extent for the box.
	 * @param	bUpdateOverlaps: if true and this shape is registered and collides, updates touching array for owner actor.
	 */
	UFUNCTION(BlueprintCallable, Category="Components|Box")
	void SetBoxExtent(FVector InBoxExtent, bool bUpdateOverlaps=true);

	// @return the box extent, scaled by the component scale.
	UFUNCTION(BlueprintCallable, Category="Components|Box")
	FVector GetScaledBoxExtent() const;

	// @return the box extent, ignoring component scale.
	UFUNCTION(BlueprintCallable, Category="Components|Box")
	FVector GetUnscaledBoxExtent() const;

	// Begin UPrimitiveComponent interface.
	virtual bool IsZeroExtent() const override;
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
	virtual struct FCollisionShape GetCollisionShape(float Inflation = 0.0f) const override;
	// End UPrimitiveComponent interface.

	// Begin USceneComponent interface
	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
	// End USceneComponent interface

	// Begin UShapeComponent interface
	virtual void UpdateBodySetup() override;
	// End UShapeComponent interface

	// Sets the box extents without triggering a render or physics update.
	FORCEINLINE void InitBoxExtent(const FVector& InBoxExtent) { BoxExtent = InBoxExtent; }
};

// ----------------- INLINES ---------------

FORCEINLINE FVector URoleManagerComponent::GetScaledBoxExtent() const
{
	//return BoxExtent * ComponentToWorld.GetScale3D();
	return BoxExtent;
}

FORCEINLINE FVector URoleManagerComponent::GetUnscaledBoxExtent() const
{
	return BoxExtent;
}
