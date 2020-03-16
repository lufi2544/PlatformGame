// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonBase.h"
#include "MovingPlatformBase.h"


#include "TargetPointBase.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"



// Sets default values
AButtonBase::AButtonBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	BoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("Trigger Space"));

	if (!ensure(BoxComponent)) { return; }

	RootComponent = BoxComponent;

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AButtonBase::OnComponentBeginOverlap);


	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AButtonBase::OnComponentEndOverlap);

	if (bIsPositionOnly)
	{
		bHasTimer = false;

	}

	
}

// Called when the game starts or when spawned
void AButtonBase::BeginPlay()
{
	Super::BeginPlay();


	AddTargetsToReachOnActivationToPlatformArray(TargetsToReachOnActivation);
	
	
}



EButtonType AButtonBase::GetButtonType()
{

	return ButtonMainType;

}

void AButtonBase::ApplyFreezeToPlatform(bool bNewPlatformState )
{
	MovingPlatformToInteract->SetbCanMove(bNewPlatformState);	
	
}

void AButtonBase::UnfreezePlatform()
{

	MovingPlatformToInteract->SetbCanMove(true);

	UE_LOG(LogTemp , Warning , TEXT("Unfreezing!"));

}

void AButtonBase::ApplySpeedToPlatform(float fNewSpeed)
{

	MovingPlatformToInteract->AddSpeed(fNewSpeed);

}



void AButtonBase::UnapplySpeedToPlatform()
{

	MovingPlatformToInteract->SetSpeed(MovingPlatformToInteract->GetLastSpeed());

}

void AButtonBase::ChangeTargetsToPlatform()
{

	MovingPlatformToInteract->SetTargetsToReach(TargetsToReachOnActivation);

}

void AButtonBase::UnchangeTargetsToPlatform()
{

	MovingPlatformToInteract->SetTargetsToReach(MovingPlatformToInteract->GetInitialTargetsReached());

}

void AButtonBase::ApplyEffect()
{

	if (ButtonMainType == EButtonType::BT_Freezer || SecundaryButtonType == EButtonType::BT_Freezer)
	{
		ApplyFreezeToPlatform(false);
	}


	if (ButtonMainType == EButtonType::BT_Speeder || SecundaryButtonType == EButtonType::BT_Speeder)
	{
	
		ApplySpeedToPlatform(fSpeedToAdd);
	
	}

	if (ButtonMainType == EButtonType::BT_Collaborative || SecundaryButtonType == EButtonType::BT_Collaborative) 
	{
	
		
		MovingPlatformToInteract->AddCollaborativeEffects();

	
	
	}

	if (ButtonMainType == EButtonType::BT_TargetChanger || SecundaryButtonType == EButtonType::BT_TargetChanger) 
	{
	
		ChangeTargetsToPlatform();

	}



		if (bHasTimer)
		{

			GetWorldTimerManager().SetTimer(TimeHandle, this, &AButtonBase::OnUnpushButton, fActivatedTime, false);

		}

	
		bIsButtonActive = true;
}

void AButtonBase::UnapplyEffect()
{
	if (ButtonMainType == EButtonType::BT_Freezer || SecundaryButtonType == EButtonType::BT_Freezer)
	{
	
		UnfreezePlatform();

	}

	if (ButtonMainType == EButtonType::BT_Speeder || SecundaryButtonType == EButtonType::BT_Speeder)
	{
	
		UnapplySpeedToPlatform();
	
	}

	if (ButtonMainType == EButtonType::BT_Collaborative || SecundaryButtonType == EButtonType::BT_Collaborative)
	{
	
		MovingPlatformToInteract->RemoveCollaborativeEffects();
	
	}

	if (ButtonMainType == EButtonType::BT_TargetChanger || SecundaryButtonType == EButtonType::BT_TargetChanger)
	{
	
		UnchangeTargetsToPlatform();
	
	}



	bIsButtonActive = false;
}

// Called every frame
void AButtonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AButtonBase::OnPushButton() 
{
	if (!ensure(MovingPlatformToInteract)) { return; }

	MovingPlatformToInteract->OnControlButtonPushed(true);

}

void AButtonBase::OnUnpushButton() 
{
	if (!ensure(MovingPlatformToInteract)) { return; }

	MovingPlatformToInteract->OnControlButtonPushed(false);

	OnTimerFinish();

}



void AButtonBase::AddTargetsToReachOnActivationToPlatformArray(TArray<ATargetPointBase*> TargetPoints)
{

	if ( !ensure( MovingPlatformToInteract ) ) { return; }

	if (TargetPoints.Num() > 0) 
	{
		
		MovingPlatformToInteract->SetTargetsToReachOnPush(TargetPoints);

	}


}



void AButtonBase::ActiveButton(bool bButtonState)
{

	if (!ensure(MovingPlatformToInteract)) { return; }

	MovingPlatformToInteract->SetIsButtonActivated(true);

}

void AButtonBase::DesactiveButton(bool bButtonState)
{
	if (!ensure(MovingPlatformToInteract)) { return; }

	MovingPlatformToInteract->SetIsButtonActivated(false);

}

//DELEGATES

void AButtonBase::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


	


	
}


void AButtonBase::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	if (!bHasTimer) 
	{
		if (MovingPlatformToInteract->GetIsCollaborativeState())
		{

			

		

		}
		else
		{



			


		}
	}

	


}


