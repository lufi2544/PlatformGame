// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonBase.h"
#include "MovingPlatformBase.h"
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
}

// Called when the game starts or when spawned
void AButtonBase::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void AButtonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//DELEGATES

void AButtonBase::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!ensure(MovingPlatformToInteract)) { return; }

	MovingPlatformToInteract->OnControlButtonPushed(true);

}

