// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AbilitySystem/Core/TCGameplayAbility.h"
#include "TCCharacterBase.generated.h"

UENUM()
enum ControlType
{
	FirstPerson     UMETA(DisplayName = "FirstPerson"),
	ThridPerson      UMETA(DisplayName = "ThridPerson")
};

UCLASS()
class THECORE_API ATCCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;


	// Sets default values for this character's properties
	ATCCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Only called on the Server. Calls before Server's AcknowledgePossession.
	virtual void PossessedBy(AController* NewController) override;

	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	TWeakObjectPtr<class UTCAbilitySystemComponent> AbilitySystemComponent;

	// Default abilities for this Character. These will be removed on Character death and regiven if Character respawns.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASDocumentation|Abilities")
		TArray<TSubclassOf<class UTCGameplayAbility>> CharacterAbilities;

	void AddCharacterAbilities();

	void BindASCInput();

	bool ASCInputBound = false;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);




	////////FIRST PERSON

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FirstPersonCameraComponent;


	//Switch
	UFUNCTION()
		void SwitchCamera(ControlType Type);

	UFUNCTION()
		void SwitchControlType();

	ControlType CurrentControlType = ControlType::ThridPerson;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeTime = 35.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float RemainLifeTime;

	FTimerHandle LifeTimeHandle;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float RemainLifeTimeDecreasePeriod = 0.1;

	UFUNCTION(BlueprintCallable)
		void DecreaseLifeTime();

	UFUNCTION(BlueprintCallable)
		void KillCharacter();
	UFUNCTION()
		void OnDeath();

	void BeginDestroy() override;
};
