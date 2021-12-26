// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Core/TCGameplayAbility.h"
#include "TCDashAbility.generated.h"

/**
 * 
 */
UCLASS()
class THECORE_API UTCDashAbility : public UTCGameplayAbility
{
	GENERATED_BODY()
		UTCDashAbility();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* MontageToPlay;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DashDuration = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DashForce = 2250;

	UFUNCTION()
		void OnCompleted();
	UFUNCTION()
		void OnCancelled();
	UFUNCTION()
		void OnForceFinished();
};
