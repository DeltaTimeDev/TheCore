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
	StartRecording();
}

// Called every frame
void ATCTimeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATCTimeManager::StartRecording()
{
	TimeSession.TimeInterval = Interval;
	bRecording = true;
	GetWorldTimerManager().SetTimer(RecordingTimer, this, &ATCTimeManager::RecordFrame, TimeSession.TimeInterval, true);





	//TArray<AActor*> FoundActors;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);
	//
	//for (AActor* FoundActor : FoundActors)
	//{
	//	TArray<UActorComponent*> TimeEntityComponents = FoundActor->GetComponentsByClass(UTCTimeEntityComponent::StaticClass());

	//	if (TimeEntityComponents.Num()>0)
	//	{
	//		UTCTimeEntityComponent* TimeComponent = Cast<UTCTimeEntityComponent>(TimeEntityComponents[0]);

	//		FTimeEntity* TimeEntity = new FTimeEntity();
	//		TimeEntity->TimeEntityComponent = TimeComponent;
	//		TimeEntity->TimeEntityComponent->IsRecording = true;
	//		TimeSession.TimeEntities.Add(TimeEntity);
	//	}
	//}
	
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
	for (UTCTimeEntityComponent* TimeComponent : TimeSession.TimeComponents)
	{
		TimeComponent->RecordFrame();
	}

	TimeSession.FrameCount++;
}

void ATCTimeManager::PlayFrame()
{
	if (CurrentPlayingFrame < TimeSession.FrameCount)
	{
		for (UTCTimeEntityComponent* TimeComponent : TimeSession.TimeComponents)
		{
			TimeComponent->SetPhysicsOff();
			TimeComponent->ApplyFrame(CurrentPlayingFrame);
			TimeComponent->IsRecording = false;
		}
		CurrentPlayingFrame++;
	}
	else
	{
		GetWorldTimerManager().ClearTimer(PlayTimer);
	}

}

void ATCTimeManager::Register(UTCTimeEntityComponent* TimeEntityComponent)
{
	TimeSession.TimeComponents.Add(TimeEntityComponent);
}

void ATCTimeManager::Unregister(UTCTimeEntityComponent* TimeEntityComponent)
{
	TimeSession.TimeComponents.Remove(TimeEntityComponent);
}
