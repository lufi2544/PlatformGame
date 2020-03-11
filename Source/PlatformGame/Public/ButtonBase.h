// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButtonBase.generated.h"


//FWD Declarations

class AMovingPlatformBase;
class UBoxComponent;


UCLASS()
class PLATFORMGAME_API AButtonBase : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AButtonBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//GETTERS


	//PROPERTIES


	//ThePlatform the Button is going to interact with.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonBase")
		AMovingPlatformBase* MovingPlatformToInteract;

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* BoxComponent;


	//FUNCTIONS

	//DELEGATES


		UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);




};

