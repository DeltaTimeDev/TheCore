// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Manager/TCTimeManager.h"
#include "TCGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class THECORE_API UTCGameInstance : public UGameInstance
{
	GENERATED_BODY()
public :

	void Init() override;

	UFUNCTION(BlueprintCallable)
		ATCTimeManager* GetTimeManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manager")
		TSubclassOf<ATCTimeManager> TimeManagerClass;

	void SwitchSpectateMode();

private:
	UPROPERTY(EditAnywhere)
		ATCTimeManager* TimeManager;
	
};
