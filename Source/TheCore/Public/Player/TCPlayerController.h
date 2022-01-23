// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TCPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THECORE_API ATCPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	
	int TotalCore = 3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int RemainCore;
};
