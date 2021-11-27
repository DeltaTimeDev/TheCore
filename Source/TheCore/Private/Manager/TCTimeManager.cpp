// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/TCTimeManager.h"
#include "Kismet/GameplayStatics.h"
#include "Main/TCGameInstance.h"

// Sets default values
ATCTimeManager::ATCTimeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetActorTickInterval(1);
}

// Called when the game starts or when spawned
void ATCTimeManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATCTimeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	/*if (bRecording)
	{
		UE_LOG(LogTemp, Warning, TEXT("Recording.."));
		RecordedPositions.Add(RecordingCharacters[0]->GetActorLocation());
	}
	if (bPlaying)
	{
		RecordingCharacters[0]->SetActorLocation(RecordedPositions.Last());
		RecordedPositions.RemoveAt(RecordedPositions.Num()-1);
	}*/

}

void ATCTimeManager::StartRecording()
{
	TimeSession.TimeInterval = Interval;

	GetWorldTimerManager().SetTimer(RecordingTimer, this, &ATCTimeManager::RecordFrame, TimeSession.TimeInterval, true);

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);
	
	for (AActor* FoundActor : FoundActors)
	{
		ITCTimeEntity* EntityActor = Cast<ITCTimeEntity>(FoundActor);
		
		if (EntityActor)
		{
			FTimeEntity* TimeEntity = new FTimeEntity();
			TimeEntity->Entity = EntityActor;
			TimeSession.TimeEntities.Add(TimeEntity);
		}
	}
	bRecording = true;
}

void ATCTimeManager::StopRecording()
{
	GetWorldTimerManager().ClearTimer(RecordingTimer);
}

void ATCTimeManager::StartPlay()
{
	bRecording = false;
	bPlaying = true;

	StopRecording();

	Cast<UTCGameInstance>(GetGameInstance())->SwitchSpectateMode();
	GetWorldTimerManager().SetTimer(PlayTimer, this, &ATCTimeManager::PlayFrame, TimeSession.TimeInterval, true);
}

void ATCTimeManager::RecordFrame()
{
	for (FTimeEntity* TimeEntity : TimeSession.TimeEntities)
	{
		TimeEntity->GetSnapShot();
	}

	TimeSession.FrameCount++;
}

void ATCTimeManager::PlayFrame()
{
	if (CurrentPlayingFrame < TimeSession.FrameCount)
	{
		for (FTimeEntity* TimeEntity : TimeSession.TimeEntities)
		{
			TimeEntity->Entity->SetPhysicsOff();
			TimeEntity->ApplySnapShot(CurrentPlayingFrame);
		}
		CurrentPlayingFrame++;
	}
	else
	{
		GetWorldTimerManager().ClearTimer(PlayTimer);
	}

}