// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TCPlayerController.h"

void ATCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	RemainCore = TotalCore;
}