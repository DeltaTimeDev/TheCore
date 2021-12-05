// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "TCCube.generated.h"

UCLASS()
class THECORE_API ATCCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATCCube();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//FTransform GetTransform();  // prototype declaration
	//void SetTransform(FTransform NewTransform);  // prototype declaration
	//void SetPhysicsOff();


	class UTCTimeEntityComponent* TimeEntityComponent;

};
