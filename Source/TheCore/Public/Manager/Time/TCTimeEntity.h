// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TCTimeEntity.generated.h"

/**
 * 
 */
UINTERFACE()
class THECORE_API UTCTimeEntity : public UInterface
{
	GENERATED_BODY()
	
};

class THECORE_API ITCTimeEntity
{
	GENERATED_BODY()

public:

	virtual FTransform GetTransform() { return FTransform(); };
	virtual void SetTransform(FTransform NewTransform) {};
	virtual void SetPhysicsOff() {};
};
