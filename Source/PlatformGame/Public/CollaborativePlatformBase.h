// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingPlatformBase.h"
#include "CollaborativePlatformBase.generated.h"

/**
 * 
 */
UCLASS(hideCategories = (PlatformSingleActivation))
class PLATFORMGAME_API ACollaborativePlatformBase : public AMovingPlatformBase
{
	GENERATED_BODY()
	

public:

	ACollaborativePlatformBase();
};
