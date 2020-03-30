// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "PlatformGame/Menu System/Interfaces/MenuInterface.h"


#include "MainMenu.generated.h"


/**
 * 
 */
UCLASS()
class PLATFORMGAME_API UMainMenu : public UUserWidget 
{
	GENERATED_BODY()


public:

	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;


	/** Called when the widget is construceted */
	virtual void NativeConstruct() override;
	

	void SetMenuInterface(IMenuInterface* MenuInterface);

	void SetUp();


	

	 

protected:

	virtual bool Initialize();







private:
		UPROPERTY( meta = (BindWidget))
		class UButton* Join;

		UPROPERTY( meta = (BindWidget))
		class UButton* Host;

		IMenuInterface* MenuInterface = nullptr;

		

//---------------------------------------------
		//FUNCTIONS




	//DELEGATES
		UFUNCTION()
		void OnHostButtontClicked();

		UFUNCTION()
		void OnJoinButtonClicked();


};
