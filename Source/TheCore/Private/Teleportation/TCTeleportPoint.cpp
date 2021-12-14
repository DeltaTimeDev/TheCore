// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleportation/TCTeleportPoint.h"

// Sets default values
ATCTeleportPoint::ATCTeleportPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneComponent->SetupAttachment(RootComponent);
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void ATCTeleportPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATCTeleportPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

