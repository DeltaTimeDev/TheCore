// Fill out your copyright notice in the Description page of Project Settings.


#include "TCMainCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

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

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm



	// Uncomment the following line to turn motion controllers on by default:
	//bUsingMotionControllers = true;

	TimeEntityComponent = CreateDefaultSubobject<UTCTimeEntityComponent>(TEXT("TimeEntity"));

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

	if (IsAiming)
	{
		FHitResult OutHit;
		FVector Start = FollowCamera->GetComponentLocation();

		Start.Z += 50.f;
		//Start.Y += 200.f;

		FVector ForwardVector = FollowCamera->GetForwardVector();
		Start += ForwardVector * 200;
		ForwardVector.Z = 0;
		FVector End = ((ForwardVector * 4500.f) + Start);
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredComponent(GetCapsuleComponent());

		//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 5);

		FCollisionQueryParams TraceParams(FName(TEXT("InteractTrace")), true, NULL);
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = true;
		TraceParams.AddIgnoredActor(this);

		//Re-initialize hit info
		FHitResult HitDetails = FHitResult(ForceInit);


		bool bIsHit = GetWorld()->LineTraceSingleByChannel(
			HitDetails,      // FHitResult object that will be populated with hit info
			Start,      // starting position
			End,        // end position
			ECC_Camera,  // collision channel - 3rd custom one
			TraceParams      // additional trace settings
		);

		FVector LocationToGetOverlap;

		if (bIsHit)
		{
			LocationToGetOverlap = HitDetails.Location;
		}
		else
		{
			// we missed
			LocationToGetOverlap = End;
		}


		TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
		traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Camera));
		TArray<AActor*> IgnoredActors;
		TArray<AActor*> OverlappedActors;
		DrawDebugSphere(GetWorld(), LocationToGetOverlap, 300, 10, FColor(181, 0, 0), false, 1, 0, 2);
		UKismetSystemLibrary::SphereOverlapActors(GetWorld(), LocationToGetOverlap, 300, traceObjectTypes, AActor::GetClass(), IgnoredActors, OverlappedActors);
		for (AActor* OA : OverlappedActors)
		{
			UE_LOG(LogTemp, Warning, TEXT("Overlapped %s"), *OA->GetName());
		}
		
	}

}

void ATCMainCharacter::StartAimFocus()
{
	IsAiming = true;
}

void ATCMainCharacter::EndAimFocus()
{
	IsAiming = false;
}

void ATCMainCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATCMainCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
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

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("RightClick", IE_Pressed, this, &ATCMainCharacter::StartAimFocus);
	PlayerInputComponent->BindAction("RightClick", IE_Released, this, &ATCMainCharacter::EndAimFocus);


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
