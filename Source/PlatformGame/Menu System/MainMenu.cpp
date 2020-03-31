// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "PlatformPuzzleGameInstance.h"


#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"





bool UMainMenu::Initialize() 
{

	bool bSuccess = Super::Initialize();



	if (!ensure(HostButton) ) { return false; }

	HostButton->OnClicked.AddDynamic(this, &UMainMenu::OnHostButtontClicked);

	if (!ensure(JoinButton)) { return false; }

	JoinButton->OnClicked.AddDynamic(this , &UMainMenu::OnJoinButtonClicked);

	UE_LOG(LogTemp, Warning, TEXT("Constrcted!"));

	if (!ensure(CancelButton)) { return false; }

	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::OnCancelButtonClicked);

	
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



void UMainMenu::OnHostButtontClicked()
{

	if (!ensure(MenuInterface)) { return; }



	MenuInterface->Host();



}

void UMainMenu::OnJoinButtonClicked()
{

	if (!ensure(MenuSwitcher)) {return;}

	if (!ensure(JoinMenu)) {return;}

	MenuSwitcher->SetActiveWidget(JoinMenu);


}

void UMainMenu::OnCancelButtonClicked() 
{
	if (!ensure(MenuSwitcher)) { return; }

	if (!ensure(CancelButton)) { return; }

	if (!ensure(MainMenu)) { return; }

	MenuSwitcher->SetActiveWidget(MainMenu);

	


}