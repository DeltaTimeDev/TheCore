// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "TCPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class THECORE_API ATCPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

	// Implement IAbilitySystemInterface
	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY()
		class UAbilitySystemComponent* AbilitySystemComponent;
};
