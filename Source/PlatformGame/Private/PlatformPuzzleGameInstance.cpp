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


	Engine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, TEXT("Hosting!!"));

}

void UPlatformPuzzleGameInstance::Join(const FString IP) 
{

	Engine->AddOnScreenDebugMessage(0, 5.f, FColor::Red,FString::Printf(TEXT("Joining %s"),*IP));

}