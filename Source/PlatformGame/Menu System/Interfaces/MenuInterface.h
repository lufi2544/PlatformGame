// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PLATFORMGAME_API IMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:

	// This is sayng hat the funciton has an empty implementation and that the implementation willl be introduced oon the class that this interface is implemented to.
	virtual void Host() = 0;

	virtual void Join(const FString IP) = 0;

};
