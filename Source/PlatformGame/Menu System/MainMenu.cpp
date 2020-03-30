// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "PlatformPuzzleGameInstance.h"

#include "Components/Button.h"





bool UMainMenu::Initialize() 
{

	bool bSuccess = Super::Initialize();



	if (!ensure(Host) ) { return false; }

	Host->OnClicked.AddDynamic(this, &UMainMenu::OnHostButtontClicked);

	if (!ensure(Join)) { return false; }

	Join->OnClicked.AddDynamic(this , &UMainMenu::OnJoinButtonClicked);

	UE_LOG(LogTemp, Warning, TEXT("Constrcted!"));

	
	SetMenuInterface(Cast<UPlatformPuzzleGameInstance>(GetGameInstance()));

		return bSuccess;
}

void UMainMenu::SetUp() 
{

	this->AddToViewport();

	if (!ensure(GetWorld()->GetFirstPlayerController())) { return; }

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();


	


}


void UMainMenu::SetMenuInterface(IMenuInterface* mMenuInterface)
{

	MenuInterface = mMenuInterface;

}


//DELEGATES


void UMainMenu::OnHostButtontClicked()
{

	if (!ensure(MenuInterface)) { return; }

	

	MenuInterface->Host();
	
	

}

void UMainMenu::OnJoinButtonClicked() 
{

	MenuInterface->Join( FString ("Hello"));


}

void UMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{


	Super::OnLevelRemovedFromWorld( InLevel, InWorld);

	FInputModeGameOnly InputDataBase;

	GetOwningPlayer()->SetInputMode(InputDataBase);

	GetOwningPlayer()->bShowMouseCursor = false;

	RemoveFromViewport();

	


}

void UMainMenu::NativeConstruct() 
{
	Super::NativeConstruct();

	APlayerController* PlayerController = GetOwningPlayer();

	FInputModeUIOnly InputDataBase;

	InputDataBase.SetWidgetToFocus(this->TakeWidget());

	InputDataBase.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputDataBase);

	PlayerController->bShowMouseCursor = true;


}
