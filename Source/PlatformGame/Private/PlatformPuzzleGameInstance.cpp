// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformPuzzleGameInstance.h"


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

	World->ServerTravel("World'/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap.ThirdPersonExampleMap' listen");


}

void UPlatformPuzzleGameInstance::Join(const FString IP) 
{

	Engine->AddOnScreenDebugMessage(0, 5.f, FColor::Red,FString::Printf(TEXT("Joining %s"),*IP));

}