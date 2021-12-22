// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TCDashAbility.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_ApplyRootMotionConstantForce.h"
#include "Player/TCCharacterBase.h"

UTCDashAbility::UTCDashAbility()
{
	AbilityInputID = ETCAbilityInputID::Ability1;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	//AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Jump")));
}
void UTCDashAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo,ActivationInfo,TriggerEventData);

	UAbilityTask_PlayMontageAndWait* Task = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, MontageToPlay,1, NAME_None,false);
	Task->OnBlendOut.AddDynamic(this, &UTCDashAbility::OnCompleted);
	Task->OnCompleted.AddDynamic(this, &UTCDashAbility::OnCompleted);
	Task->OnInterrupted.AddDynamic(this, &UTCDashAbility::OnCancelled);
	Task->OnCancelled.AddDynamic(this, &UTCDashAbility::OnCancelled);
	//Task->EventReceived.AddDynamic(this, &UKBBasicAbility::EventReceived);
	// ReadyForActivation() is how you activate the AbilityTask in C++. Blueprint has magic from K2Node_LatentGameplayTaskCall that will automatically call ReadyForActivation().
	Task->ReadyForActivation();

	UAbilityTask_ApplyRootMotionConstantForce* RootMotionTask = UAbilityTask_ApplyRootMotionConstantForce::ApplyRootMotionConstantForce(this, NAME_None, CharacterBase->GetActorForwardVector(), 2250, 0.8f, false, nullptr, ERootMotionFinishVelocityMode::SetVelocity, CharacterBase->GetVelocity(), 0, false);
	RootMotionTask->OnFinish.AddDynamic(this, &UTCDashAbility::OnForceFinished);
	RootMotionTask->ReadyForActivation();
}

void UTCDashAbility::OnCompleted()
{

}

void UTCDashAbility::OnCancelled()
{

}

void UTCDashAbility::OnForceFinished()
{
}
