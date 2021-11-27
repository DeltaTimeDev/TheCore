// Fill out your copyright notice in the Description page of Project Settings.


#include "TCCube.h"

// Sets default values
ATCCube::ATCCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void ATCCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATCCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FTransform ATCCube::GetTransform()
{
	return GetActorTransform();
}

void ATCCube::SetTransform(FTransform NewTransform)
{
	SetActorTransform(NewTransform);
}

void ATCCube::SetPhysicsOff()
{
	Mesh->SetSimulatePhysics(false);
}

