// Fill out your copyright notice in the Description page of Project Settings.


#include "TCDoor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATCDoor::ATCDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneComponent->SetupAttachment(RootComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(SceneComponent);
	//MeshComponent-
}

// Called when the game starts or when spawned
void ATCDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATCDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATCDoor::Open()
{
	MeshComponent->SetRelativeLocation(FVector(0, 100, 0));
}

void ATCDoor::Close()
{
	MeshComponent->SetRelativeLocation(FVector(0, 0, 0));
}

