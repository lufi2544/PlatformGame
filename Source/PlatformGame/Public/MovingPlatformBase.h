// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatformBase.generated.h"


//FWD Delcarations

class ATargetPointBase;

/**
 * 
 */
UCLASS()
class PLATFORMGAME_API AMovingPlatformBase : public AStaticMeshActor
{

	GENERATED_BODY()

public:


	AMovingPlatformBase();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	//PROPERTIES


	//Targets that the platform will move between
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlatformBase")
		TArray<ATargetPointBase*>TargetsToReach;

	// If true The Platform will move between the given Targets with a random movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlatformBase")
		bool RandomMovementToTargets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlatformBase", meta = (DisplayName = "CanMove"))
		bool bCanMove;

	UPROPERTY(EditAnywhere, Category = "PlatformBase", meta = (ClampMin = -2.f), meta = (ClampMax = 2.f), meta = (DisplayName = "Speed"))
		float fSpeed = 1.f;

	//Targets that the platform will move between when we push a button
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlatformBase")
		TArray<ATargetPointBase*>TargetsToReachOnButonPush;

	//Changes the mode to as if a button would have triggered the current platform
	UPROPERTY(EditAnywhere, Category = "PlatformBase")
		bool IsButtonActive;



	bool bIsReaching = false;

	int32 ArrayCounter = 0;

	ATargetPointBase* PlatformReaching;

	ATargetPointBase* LastPlatformReached;


	//GETTERS






	//FUNCTIONS


	


	/*Change the targets to reach by the platform based on a button being pushed*/
	UFUNCTION(BlueprintCallable, category = "PlatformBase")
		bool OnControlButtonPushed(bool bIsButtonactive);



	bool PlatformGo(ATargetPointBase* TargetPoint);

	bool PlatformMoveToTatgets(TArray<ATargetPointBase*> Targets, bool bHasRandomMovement);








	//VARIABLES






	//DELEGATES












};
