// Fill out your copyright notice in the Description page of Project Settings.

#include "AVG.h"
#include "RoleActor.h"


// Sets default values
ARoleActor::ARoleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoleActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

