// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "AVGPrivatePCH.h"
#include "RoleManagerComponent.h"
#include "Runtime/Engine/Public/ContentStreaming.h"
#define LOCTEXT_NAMESPACE "Role"

URoleManagerComponent::URoleManagerComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BoxExtent = FVector(32.0f, 32.0f, 32.0f);

	bUseEditorCompositing = true;
}


void URoleManagerComponent::SetBoxExtent(FVector NewBoxExtent, bool bUpdateOverlaps)
{
	BoxExtent = NewBoxExtent;
	MarkRenderStateDirty();

	// do this if already created
	// otherwise, it hasn't been really created yet
	if (bPhysicsStateCreated)
	{
		DestroyPhysicsState();
		UpdateBodySetup();
		CreatePhysicsState();

		if ( bUpdateOverlaps && IsCollisionEnabled() && GetOwner() )
		{
			UpdateOverlaps();
		}
	}
}

void URoleManagerComponent::UpdateBodySetup()
{
	if(ShapeBodySetup == NULL || ShapeBodySetup->IsPendingKill())
	{
		ShapeBodySetup = NewObject<UBodySetup>(this);
		ShapeBodySetup->CollisionTraceFlag = CTF_UseSimpleAsComplex;
		ShapeBodySetup->AggGeom.BoxElems.Add(FKBoxElem());
	}

	check(ShapeBodySetup->AggGeom.BoxElems.Num() == 1);
	FKBoxElem* se = ShapeBodySetup->AggGeom.BoxElems.GetData();

	// @todo UE4 do we allow this now?
	// check for malformed values
	if( BoxExtent.X < KINDA_SMALL_NUMBER )
	{
		BoxExtent.X = 1.0f;
	}

	if( BoxExtent.Y < KINDA_SMALL_NUMBER )
	{
		BoxExtent.Y = 1.0f;
	}

	if( BoxExtent.Z < KINDA_SMALL_NUMBER )
	{
		BoxExtent.Z = 1.0f;
	}

	// now set the PhysX data values
	se->SetTransform( FTransform::Identity );
	se->X = BoxExtent.X*2;
	se->Y = BoxExtent.Y*2;
	se->Z = BoxExtent.Z*2;
}

bool URoleManagerComponent::IsZeroExtent() const
{
	return BoxExtent.IsZero();
}

FBoxSphereBounds URoleManagerComponent::CalcBounds(const FTransform& LocalToWorld) const 
{
	return FBoxSphereBounds( FBox( -BoxExtent, BoxExtent ) ).TransformBy(LocalToWorld);
}



FPrimitiveSceneProxy* URoleManagerComponent::CreateSceneProxy()
{
	/** Represents a UCapsuleComponent to the scene manager. */
	class FBoxSceneProxy : public FPrimitiveSceneProxy
	{
	public:
		FBoxSceneProxy(const URoleManagerComponent* InComponent)
			:	FPrimitiveSceneProxy(InComponent)
			,	bDrawOnlyIfSelected( InComponent->bDrawOnlyIfSelected )
			,   BoxExtents( InComponent->BoxExtent )
			,	BoxColor( InComponent->ShapeColor )
		{
			bWillEverBeLit = false;
		}

		virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override
		{
			QUICK_SCOPE_CYCLE_COUNTER( STAT_BoxSceneProxy_GetDynamicMeshElements );

			const FMatrix& LocalToWorld = GetLocalToWorld();
			
			for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++)
			{
				if (VisibilityMap & (1 << ViewIndex))
				{
					const FSceneView* View = Views[ViewIndex];

					const FLinearColor DrawColor = GetViewSelectionColor(BoxColor, *View, IsSelected(), IsHovered(), false, IsIndividuallySelected() );

					FPrimitiveDrawInterface* PDI = Collector.GetPDI(ViewIndex);
					DrawOrientedWireBox(PDI, LocalToWorld.GetOrigin(), LocalToWorld.GetScaledAxis( EAxis::X ), LocalToWorld.GetScaledAxis( EAxis::Y ), LocalToWorld.GetScaledAxis( EAxis::Z ), BoxExtents, DrawColor, SDPG_World);
				}
			}
		}

		virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) override
		{
			const bool bVisible = !bDrawOnlyIfSelected || IsSelected();

			FPrimitiveViewRelevance Result;
			Result.bDrawRelevance = IsShown(View) && bVisible;
			Result.bDynamicRelevance = true;
			Result.bShadowRelevance = IsShadowCast(View);
			Result.bEditorPrimitiveRelevance = UseEditorCompositing(View);
			return Result;
		}
		virtual uint32 GetMemoryFootprint( void ) const override { return( sizeof( *this ) + GetAllocatedSize() ); }
		uint32 GetAllocatedSize( void ) const { return( FPrimitiveSceneProxy::GetAllocatedSize() ); }

	private:
		const uint32	bDrawOnlyIfSelected:1;
		const FVector	BoxExtents;
		const FColor	BoxColor;
	};

	return new FBoxSceneProxy( this );
}


FCollisionShape URoleManagerComponent::GetCollisionShape(float Inflation) const
{
	FVector Extent = GetScaledBoxExtent() + Inflation;
	if (Inflation < 0.f)
	{
		// Don't shrink below zero size.
		Extent = Extent.ComponentMax(FVector::ZeroVector);
	}

	return FCollisionShape::MakeBox(Extent);
}

bool URoleManagerComponent::SetRoleManager(class URoleManager* NewSprite)
{
	if (NewSprite != SourceSprite)
	{
		// Don't allow changing the sprite if we are "static".
		AActor* Owner = GetOwner();
		if (!IsRegistered() || (Owner == nullptr) || (Mobility != EComponentMobility::Static))
		{
			SourceSprite = NewSprite;

			// Need to send this to render thread at some point
			MarkRenderStateDirty();

			// Update physics representation right away
			RecreatePhysicsState();

			// Notify the streaming system. Don't use Update(), because this may be the first time the mesh has been set
			// and the component may have to be added to the streaming system for the first time.
			IStreamingManager::Get().NotifyPrimitiveAttached(this, DPT_Spawned);

			// Since we have new mesh, we need to update bounds
			UpdateBounds();

			return true;
		}
	}
	return false;
}

URoleManager* URoleManagerComponent::GetRoleManager()
{
	return SourceSprite;
}

#undef LOCTEXT_NAMESPACE