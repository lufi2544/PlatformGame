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

}

void AButtonBase::AddTargetsToReachOnActivationToPlatformArray(TArray<ATargetPointBase*> TargetPoints)
{

	if ( !ensure( MovingPlatformToInteract ) ) { return; }

	if (TargetPoints.Num() > 0) 
	{
		for (ATargetPointBase* Target : TargetPoints)
		{

			MovingPlatformToInteract->TargetsToReachOnButonPush.Add(Target);

		}
	
	}


}

//DELEGATES

void AButtonBase::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if( TargetsToReachOnActivation.Num() > 0 )

	OnPushButton();


	if (bHasTimer)
		{

	GetWorldTimerManager().SetTimer(TimeHandle, this, &AButtonBase::OnUnpushButton, fActivatedTime, false);
		}
	}


void AButtonBase::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{

	UE_LOG(LogTemp , Warning , TEXT("End Overlapping!!"));
	if (bIsPositionOnly) 
	{
	
		OnUnpushButton();
	
	}

}
