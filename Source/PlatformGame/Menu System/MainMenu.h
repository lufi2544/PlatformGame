// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMGAME_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()


public:



protected:

	virtual bool Initialize();




private:
		UPROPERTY( meta = (BindWidget))
		class UButton* Join;

		UPROPERTY( meta = (BindWidget))
		class UButton* Host;


//---------------------------------------------
		//FUNCTIONS




	//DELEGATES
		UFUNCTION()
		void OnHostButtontClicked();

		UFUNCTION()
		void OnJoinButtonClicked();


};
