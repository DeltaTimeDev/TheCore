// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/Time/TCTimeEntityComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Main/TCGameInstance.h"

// Sets default values for this component's properties
UTCTimeEntityComponent::UTCTimeEntityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTCTimeEntityComponent::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UTCGameInstance>(UGameplayStatics::GetGameInstance(this));
	TimeManager = GameInstance->GetTimeManager();
	TimeManager->Register(this);
	
}


// Called every frame
void UTCTimeEntityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FTransform UTCTimeEntityComponent::GetTransform()
{
	return GetOwner()->GetActorTransform();
}

void UTCTimeEntityComponent::SetTransform(FTransform NewTransform)
{
	GetOwner()->SetActorTransform(NewTransform);
}

void UTCTimeEntityComponent::SetPhysicsOff()
{
	UPrimitiveComponent* Root = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (Root)
	{
		Root->SetSimulatePhysics(false);
	}
}

void UTCTimeEntityComponent::SetSpeed(float NewSpeed)
{
	Speed = NewSpeed;
}

float UTCTimeEntityComponent::GetSpeed()
{
	if (IsRecording)
	{
		return GetOwner()->GetVelocity().Size();
	}

	return Speed;
}

FTimeFrame UTCTimeEntityComponent::SnapShootFrame()
{
	FTimeFrame Frame;
	Frame.EntitySpeed = GetSpeed();
	Frame.EntityTransform = GetTransform();
	return Frame;
}

void UTCTimeEntityComponent::ApplyFrame(int32 NewFrameIndex)
{
	if (RecordedFrames.IsValidIndex(NewFrameIndex))
	{
		FTimeFrame NewFrame = RecordedFrames[NewFrameIndex];
		SetSpeed(NewFrame.EntitySpeed);
		SetTransform(NewFrame.EntityTransform);
	}

}

void UTCTimeEntityComponent::RecordFrame()
{
	RecordedFrames.Add(SnapShootFrame());
}

