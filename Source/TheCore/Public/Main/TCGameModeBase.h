// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TCGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class THECORE_API ATCGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		ATCGameModeBase();
public:
	void StartPlay() override;

};
