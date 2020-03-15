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

	return ButtonType;

}

void AButtonBase::ApplyFreezeToPlatform(bool bNewPlatformState ,bool bPlatformHasTimer , float fTimerTime)
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



void AButtonBase::UnapplyuSpeedToPlatform()
{

	MovingPlatformToInteract->SetSpeed(MovingPlatformToInteract->GetLastSpeed());

}

void AButtonBase::ApplyEffect()
{

	if (ButtonType == EButtonType::BT_Freezer)
	{
		ApplyFreezeToPlatform(false, bHasTimer, fActivatedTime);
	}


	if (ButtonType == EButtonType::BT_Speeder) 
	{
	
		ApplySpeedToPlatform(fSpeedToAdd);
	
	}



		if (bHasTimer)
		{

			GetWorldTimerManager().SetTimer(TimeHandle, this, &AButtonBase::OnUnpushButton, fActivatedTime, false);

		}

	

}

void AButtonBase::UnapplyEffect()
{
	if (ButtonType == EButtonType::BT_Freezer) 
	{
	
		UnfreezePlatform();

	}

	if (ButtonType == EButtonType::BT_Speeder) 
	{
	
		UnapplyuSpeedToPlatform();
	
	}


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

			DesactiveButton(false);

			MovingPlatformToInteract->SetbCanMove(true);

		}
		else
		{



			


		}
	}

	


}


