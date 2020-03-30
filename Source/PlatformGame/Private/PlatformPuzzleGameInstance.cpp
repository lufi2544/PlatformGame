// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformPuzzleGameInstance.h"

#include "GameFramework/PlayerController.h"

#include "Engine/Engine.h"
#include "PlatformGame/Menu System/MainMenu.h"
#include "UObject/ConstructorHelpers.h"

#include "Components/Widget.h"
#include "MovingPlatformBase.h"
#include "ButtonBase.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"




UPlatformPuzzleGameInstance::UPlatformPuzzleGameInstance(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UMainMenu>DefaultMenuWidget(TEXT("WidgetBlueprint'/Game/UI/MenuUI/WB_MainMenu'"));

	if (!ensure(DefaultMenuWidget.Class)) { return; }

	UserMenuWidgetClass = DefaultMenuWidget.Class;

	UE_LOG(LogTemp, Error, TEXT("The Menu Widget Clss Name is %s"), *UserMenuWidgetClass->GetName());

}

void UPlatformPuzzleGameInstance::LoadMenu() 
{

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (!ensure(PlayerController)) { return; }

	UMainMenu* wMenu = CreateWidget<UMainMenu>(this, UserMenuWidgetClass);

	if (!ensure(wMenu)) { return; }

	wMenu->AddToPlayerScreen();

	wMenu->SetMenuInterface(this);

}

void UPlatformPuzzleGameInstance::Init() 
{

	Engine = GetEngine();

}




void UPlatformPuzzleGameInstance::Host() 
{


	UWorld* World = GetWorld();

	Engine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, TEXT("Hosting!!"));

	if (!ensure(World)) { return; }

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap");

	

}

void UPlatformPuzzleGameInstance::Join(const FString IP) 
{

	Engine->AddOnScreenDebugMessage(0, 5.f, FColor::Red,FString::Printf(TEXT("Joining %s"),*IP));

	APlayerController* PlayerController = GetFirstLocalPlayerController();

	if (!ensure(PlayerController)) { return; }

	PlayerController->ClientTravel(IP, ETravelType::TRAVEL_Absolute);

}

