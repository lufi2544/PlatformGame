// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButtonBase.generated.h"


//FWD Declarations

class AMovingPlatformBase;
class UBoxComponent;
class ATargetPointBase;


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

	/*Targets that the platform will reach on activation*/
	UPROPERTY(EditAnywhere, Category = "ButtonBase")
	TArray<ATargetPointBase*> TargetsToReachOnActivation;

	/*If true the current button just affects the platform if the player is on top of it.
	  If Has Timer is activated, it will be automatically desactivated.
	*/
	UPROPERTY(EditAnywhere, Category = "ButtonBase" , meta = (DisplayName = "IsPositionOnly"))
	bool bIsPositionOnly;

	/*Determines wether the button has a timer which deactivates the function activated when pushed the button*/
	UPROPERTY(EditAnywhere ,  Category = "ButtonBase" , meta=(DisplayName ="HasTimer"))
	bool bHasTimer;

	/*Time that the activated function by the button will last (if HasTimer is true) */
	UPROPERTY(EditAnywhere , Category = "ButtonBase" , meta = (DisplayName = "DeactivationTime"))
	float fActivatedTime;


	FTimerHandle TimeHandle;

	//FUNCTIONS

	void OnPushButton();

	void OnUnpushButton();

	void AddTargetsToReachOnActivationToPlatformArray(TArray<ATargetPointBase*> TargetPoints);

	//DELEGATES


		UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		UFUNCTION()
		void OnComponentEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};

