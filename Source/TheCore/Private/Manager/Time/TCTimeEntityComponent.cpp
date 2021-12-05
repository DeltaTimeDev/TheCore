// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/Time/TCTimeEntityComponent.h"

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

	// ...
	
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
	//GetOwner()->
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

void UTCTimeEntityComponent::ApplyFrame(FTimeFrame NewFrame)
{
	SetSpeed(NewFrame.EntitySpeed);
	SetTransform(NewFrame.EntityTransform);
}

