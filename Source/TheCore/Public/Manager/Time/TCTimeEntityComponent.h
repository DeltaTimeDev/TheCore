// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TCTimeEntityComponent.generated.h"


USTRUCT(BlueprintType)
struct FTimeFrame
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test Variables")
		FTransform EntityTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test Variables")
		float EntitySpeed;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THECORE_API UTCTimeEntityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTCTimeEntityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	FTransform GetTransform();
	void SetTransform(FTransform NewTransform);
	void SetPhysicsOff();
	void SetSpeed(float NewSpeed);

	UFUNCTION(BlueprintCallable)
	float GetSpeed();

	FTimeFrame SnapShootFrame();
	void ApplyFrame(FTimeFrame NewFrame);

	float Speed=0;


	bool IsRecording;
		
};
