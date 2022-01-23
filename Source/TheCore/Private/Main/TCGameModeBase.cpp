// Fill out your copyright notice in the Description page of Project Settings.


#include "Main/TCGameModeBase.h"

ATCGameModeBase::ATCGameModeBase()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/BP/TimeEntites/TimeCharacterBase.TimeCharacterBase_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ATCGameModeBase::StartPlay()
{
	Super::StartPlay();
}