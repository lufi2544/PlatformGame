// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"





bool UMainMenu::Initialize() 
{

	bool bSuccess = Super::Initialize();



	if (!ensure(Host) ) { return false; }

	Host->OnClicked.AddDynamic(this, &UMainMenu::OnHostButtontClicked);

	if (!ensure(Join)) { return false; }

	Join->OnClicked.AddDynamic(this , &UMainMenu::OnJoinButtonClicked);

	UE_LOG(LogTemp, Warning, TEXT("Constrcted!"));


		return bSuccess;
}

//DELEGATES


void UMainMenu::OnHostButtontClicked()
{

	UE_LOG(LogTemp, Warning, TEXT("Pressing the Host  Button!"));

}

void UMainMenu::OnJoinButtonClicked() 
{

	UE_LOG(LogTemp , Warning , TEXT("The Join Button is being clicked!!"));

}