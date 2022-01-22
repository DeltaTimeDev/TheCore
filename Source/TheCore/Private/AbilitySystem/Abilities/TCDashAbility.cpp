// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TCDashAbility.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_ApplyRootMotionConstantForce.h"
#include "Player/TCCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "Abilities/GameplayAbilityTargetActor.h"

UTCDashAbility::UTCDashAbility()
{
	AbilityInputID = ETCAbilityInputID::Ability1;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	//AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Jump")));
}
void UTCDashAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	//UAbilityTask_WaitTargetData* Wait = UAbilityTask_WaitTargetData::WaitTargetData(this, TEXT("a"), EGameplayTargetingConfirmation::UserConfirmed, SingleLineTrace);
	//Wait->On
	//Wait->ReadyForActivation();

	//CharacterBase->GetCharacterMovement()->GravityScale = 0;

	UAbilityTask_PlayMontageAndWait* Task = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, MontageToPlay, 1, NAME_None, false);
	Task->OnBlendOut.AddDynamic(this, &UTCDashAbility::OnCompleted);
	Task->OnCompleted.AddDynamic(this, &UTCDashAbility::OnCompleted);
	Task->OnInterrupted.AddDynamic(this, &UTCDashAbility::OnCancelled);
	Task->OnCancelled.AddDynamic(this, &UTCDashAbility::OnCancelled);
	//Task->EventReceived.AddDynamic(this, &UKBBasicAbility::EventReceived);
	// ReadyForActivation() is how you activate the AbilityTask in C++. Blueprint has magic from K2Node_LatentGameplayTaskCall that will automatically call ReadyForActivation().
	Task->ReadyForActivation();
	
	
	//AGameplayAbilityTargetActor* Test;
	//Test->StartLocation

	//UAbilityTask_WaitTargetData* WaitTargetDataTask = UAbilityTask_WaitTargetData::WaitTargetDataUsingActor(this, NAME_None, EGameplayTargetingConfirmation::UserConfirmed, Test);
	//WaitTargetDataTask->
	
	//WaitTargetDataTask->ReadyForActivation();


	FVector PushDirection = CharacterBase->FollowCamera->GetComponentRotation().Vector();

	UAbilityTask_ApplyRootMotionConstantForce* RootMotionTask = UAbilityTask_ApplyRootMotionConstantForce::ApplyRootMotionConstantForce(this, NAME_None, PushDirection/*CharacterBase->GetActorForwardVector()*/, DashForce, DashDuration, false, nullptr, ERootMotionFinishVelocityMode::SetVelocity, CharacterBase->GetVelocity(), 0, false);
	RootMotionTask->OnFinish.AddDynamic(this, &UTCDashAbility::OnForceFinished);
	RootMotionTask->ReadyForActivation();

	/*FVector StartLine = CharacterBase->GetActorLocation();
	FVector EndLine = CharacterBase->GetActorLocation() + CharacterBase->GetActorForwardVector()*100;
	DrawDebugDirectionalArrow(GetWorld(), StartLine, EndLine, 120.f, FColor::Magenta, true, -1.f, 0, 5.f);*/

	FVector StartLine = CharacterBase->GetActorLocation();
	FVector EndLine = StartLine + PushDirection * 400;
	DrawDebugDirectionalArrow(GetWorld(), StartLine, EndLine, 120.f, FColor::Red, false, 4, 0, 5.f);



	float a = CharacterBase->GetCharacterMovement()->GravityScale;
	UE_LOG(LogTemp, Warning, TEXT("GetGravityZ %f"), a);
	
	UE_LOG(LogTemp, Warning, TEXT("GetGravityZ %f"), a);
}

void UTCDashAbility::OnCompleted()
{

}

void UTCDashAbility::OnCancelled()
{

}

void UTCDashAbility::OnForceFinished()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	float a = CharacterBase->GetCharacterMovement()->GravityScale = 1;
	UE_LOG(LogTemp, Warning, TEXT("GetGravityZ %f"), a);
}
