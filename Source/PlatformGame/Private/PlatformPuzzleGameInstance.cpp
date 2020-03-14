// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformPuzzleGameInstance.h"

#include "GameFramework/PlayerController.h"

#include "Engine/Engine.h"




UPlatformPuzzleGameInstance::UPlatformPuzzleGameInstance(const FObjectInitializer& ObjectInitializer)
{


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