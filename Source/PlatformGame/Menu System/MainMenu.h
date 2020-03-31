// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "PlatformGame/Menu System/Interfaces/MenuInterface.h"


#include "MainMenu.generated.h"



class UWidgetSwitcher;

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

	//MENUS
	
		UPROPERTY(meta = (BindWidget))
		class UWidget* MainMenu;


		UPROPERTY(meta = (BindWidget)) // It can be a UWidget, as long as you have the UWidget root you will be fine
		class UWidget* JoinMenu;




	//BUTTONS

		UPROPERTY(meta = (BindWidget))
		class UButton* JoinButton;

		UPROPERTY(meta = (BindWidget))
		class UButton* HostButton;

		UPROPERTY(meta = (BindWidget))
		class UButton* CancelButton;

	

	//COMPONENTS

		UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* MenuSwitcher;
		


		IMenuInterface* MenuInterface = nullptr;

		

//---------------------------------------------
		//FUNCTIONS




	//DELEGATES
		UFUNCTION()
		void OnHostButtontClicked();

		UFUNCTION()
		void OnJoinButtonClicked();

		UFUNCTION()
		void OnCancelButtonClicked();



};
