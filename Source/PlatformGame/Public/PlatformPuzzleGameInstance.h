// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlatformPuzzleGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMGAME_API UPlatformPuzzleGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:


		UPlatformPuzzleGameInstance(const FObjectInitializer &ObjectInitializer);

		virtual void Init() ;
	
};
