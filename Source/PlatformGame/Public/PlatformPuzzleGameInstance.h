// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "PlatformGame/Menu System/Interfaces/MenuInterface.h"

#include "PlatformPuzzleGameInstance.generated.h"

/**
 * 
 */

class UMainMenu;

UCLASS()
class PLATFORMGAME_API UPlatformPuzzleGameInstance : public UGameInstance , public IMenuInterface
{
	GENERATED_BODY()

public:


		UPlatformPuzzleGameInstance(const FObjectInitializer &ObjectInitializer);

		virtual void Init() ;


		/*FUNCTIONS*/
	

		UFUNCTION(BlueprintCallable , Category = "GameBase")
		void LoadMenu();

		UFUNCTION(Exec)
		virtual void Host() override;

		UFUNCTION(Exec)
		virtual void Join(const FString IP) override;


		UMainMenu* wMenuWidget = nullptr;


private:

	




	UEngine* Engine = nullptr;

	TSubclassOf<UUserWidget>UserMenuWidgetClass;

	APlayerController* pPlayerController;

	
	
	
};
