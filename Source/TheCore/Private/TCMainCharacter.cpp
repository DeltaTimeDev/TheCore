// Fill out your copyright notice in the Description page of Project Settings.


#include "TCMainCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ATCMainCharacter::ATCMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	// Uncomment the following line to turn motion controllers on by default:
	//bUsingMotionControllers = true;

}

// Called when the game starts or when spawned
void ATCMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATCMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATCMainCharacter::MoveForward(float Val)
{
	if (Val != 0.0f) AddMovementInput(GetActorForwardVector(), Val);
}

void ATCMainCharacter::MoveRight(float Val)
{
	if (Val != 0.0f) AddMovementInput(GetActorRightVector(), Val);
}

void ATCMainCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATCMainCharacter::LookUpAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

// Called to bind functionality to input
void ATCMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ATCMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATCMainCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATCMainCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATCMainCharacter::LookUpAtRate);

}

FTransform ATCMainCharacter::GetTransform()
{
	return GetActorTransform();
}

void ATCMainCharacter::SetTransform(FTransform NewTransform)
{
	SetActorTransform(NewTransform);
}



