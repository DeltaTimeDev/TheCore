// Fill out your copyright notice in the Description page of Project Settings.


#include "Main/TCGameInstance.h"
#include "GameFramework/DefaultPawn.h"
#include "Kismet/GameplayStatics.h"

void UTCGameInstance::Init()
{
	if (TimeManagerClass)
	{
		TimeManager = GetWorld()->SpawnActor<ATCTimeManager>(TimeManagerClass);		
	}
}

ATCTimeManager* UTCGameInstance::GetTimeManager()
{
	return TimeManager;
}

void UTCGameInstance::SwitchSpectateMode()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADefaultPawn::StaticClass(), FoundActors);
	if (FoundActors.Num()>0)
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(Cast<ADefaultPawn>(FoundActors[0]));
	}

}

void UTCGameInstance::StartRecording()
{
	if (TimeManager)
	{
		TimeManager->StartRecording();
	}
}

void UTCGameInstance::PlayRecord()
{
	if (TimeManager)
	{
		TimeManager->StartPlay();
	}
}

void UTCGameInstance::StopRecordingAndPlayRecord()
{
	if (TimeManager)
	{
		TimeManager->StartPlay();
	}
}
