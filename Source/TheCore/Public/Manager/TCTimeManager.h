// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Manager/Time/TCTimeEntityComponent.h"
#include "TCTimeManager.generated.h"


USTRUCT(BlueprintType)
struct FTimeSession
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test Variables")
		int32 TimeSecond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test Variables")
		float TimeInterval;

	int32 FrameCount = 0;

	TArray<UTCTimeEntityComponent*> TimeComponents;
};

UCLASS()
class THECORE_API ATCTimeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATCTimeManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeManager")
		float Interval = 1;

	UFUNCTION(BlueprintCallable)
		void StartRecording();

	UFUNCTION(BlueprintCallable)
		void StopRecording();

	UFUNCTION(BlueprintCallable)
		void StartPlay();

	UFUNCTION(BlueprintCallable)
		void RecordFrame();

	UFUNCTION(BlueprintCallable)
		void PlayFrame();

	UFUNCTION()
		void Register(UTCTimeEntityComponent* TimeEntityComponent);

	UFUNCTION()
		void Unregister(UTCTimeEntityComponent* TimeEntityComponent);


	bool bRecording = false;
	bool bPlaying = false;

	UPROPERTY()
		FTimerHandle RecordingTimer;

	UPROPERTY()
		FTimerHandle PlayTimer;

	UPROPERTY()
		FTimeSession TimeSession;

	int32 CurrentPlayingFrame = 0;




};
