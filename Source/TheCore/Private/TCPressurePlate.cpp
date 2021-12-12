// Fill out your copyright notice in the Description page of Project Settings.


#include "TCPressurePlate.h"
#include "Components/BoxComponent.h"
#include "TCDoor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATCPressurePlate::ATCPressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;


	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(BoxComponent);

	//MeshComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATCPressurePlate::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATCPressurePlate::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ATCPressurePlate::OnOverlapEnd);
}

// Called every frame
void ATCPressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATCPressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin"));

	OnOpened();
}

void ATCPressurePlate::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapEnd"));

	OnClosed();
}

void ATCPressurePlate::OnOpened()
{
	MeshComponent->SetRelativeScale3D(FVector(.5, .5, .5));
	UE_LOG(LogTemp, Warning, TEXT("OnOpened"));
	if (Door)
	{
		Door->Open();
	}
}

void ATCPressurePlate::OnClosed()
{
	MeshComponent->SetRelativeScale3D(FVector(1, 1, 1));
	UE_LOG(LogTemp, Warning, TEXT("OnClosed"));

	if (Door)
	{
		Door->Close();
	}
}

