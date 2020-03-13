// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatformBase.generated.h"


//FWD Delcarations

class ATargetPointBase;


USTRUCT(BlueprintType)

struct FMySparseClassData
{
	GENERATED_BODY()


		FMySparseClassData()
		: bIsCollaborative(false)
		, nPlatformDefaultName("NAME_None")
		{}

	UPROPERTY(EditDefaultsOnly, Category ="PlatformBase" , meta = (DisplayName = "Is Collaborative"))
	bool bIsCollaborative;

	UPROPERTY(EditDefaultsOnly , Category ="PlatformBase" , meta = (DisplayName = "Platform Default Name"))
	FName nPlatformDefaultName;


};

/**
 * 
 */
UCLASS(BlueprintType , SparseClassDataTypes = MySparseClassData)
class PLATFORMGAME_API AMovingPlatformBase : public AStaticMeshActor
{

	GENERATED_BODY()


		//SPARSEDATA/////
public:

#if WITH_EDITOR

virtual void MoveDataToSparseClassDataStruct() const override;

#endif

private:

#if WITH_EDITORONLY_DATA

private:


	UPROPERTY()
	bool bIsCollaborative_DEPRECATED;

	UPROPERTY()
	FName nDefaultPlatformName_DEPRECATED;

#endif

	//////////////////////////////////



public:

	AMovingPlatformBase();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;



	//PROPERTIES


	
private:

	//Targets that the platform will move between
	UPROPERTY(EditAnywhere, Category = "PlatformBase")
		TArray<ATargetPointBase*>TargetsToReach;

	// If true The Platform will move between the given Targets with a random movement
	UPROPERTY(EditAnywhere, Category = "PlatformBase")
		bool RandomMovementToTargets;

	UPROPERTY(EditAnywhere, Category = "PlatformBase", meta = (DisplayName = "CanMove"))
		bool bCanMove;

	UPROPERTY(EditAnywhere, Category = "PlatformBase", meta = (ClampMin = 0.f), meta = (ClampMax = 500.f), meta = (DisplayName = "Speed"))
		float fSpeed = 50.f;

	//Changes the mode to as if a button would have triggered the current platform
	UPROPERTY(EditAnywhere, Category = "PlatformBase")
		bool IsButtonActive;


	//Targets that the platform will move between when we push a button
	TArray<ATargetPointBase*>TargetsToReachOnButonPush;

	bool bIsReaching = false;

	int32 ArrayCounter = 0;

	ATargetPointBase* InitialTarget;

	ATargetPointBase* LastTarget;

	ATargetPointBase* TargetReaching;

	ATargetPointBase* LastTargetReached;

	bool bIsButtonActivated = false;




	//GETTERS

public:

	UFUNCTION(BlueprintPure, Category = "PlatformBase")
		bool GetIsCollaborativeState();

	UFUNCTION(BlueprintPure, Category = "PlatformBase")
		bool GetIsButtonActivated();


	UFUNCTION(BlueprintCallable, Category = "PlatformBase")
		void SetIsButtonActivated(bool bNewState);


	UFUNCTION(BlueprintPure, Category = "PlatformBase")
		TArray<ATargetPointBase*> GetTargetsToReach();


	UFUNCTION(BlueprintCallable, Category = "PlatformBase")
		void SetTargetsToReach(TArray<ATargetPointBase*> NewTargets);


	UFUNCTION(BlueprintPure, Category = "PlatformBase")
		bool GetCanMove();


	UFUNCTION(BlueprintCallable, Category = "PlatformBase")
		void SetbCanMove(bool bNewMovementState);


	UFUNCTION(BlueprintPure, Category = "PlatformBase")
		TArray<ATargetPointBase*> GetTargetsToReachOnPush();


	UFUNCTION(BlueprintCallable, Category = "PlatformBase")
		void SetTargetsToReachOnPush(TArray<ATargetPointBase*> NewTargets);





	//FUNCTIONS


	/*Change the targets to reach by the platform based on a button being pushed*/
	UFUNCTION(BlueprintCallable, category = "PlatformBase")
		bool OnControlButtonPushed(bool bIsButtonactive);

	


	bool PlatformGo(ATargetPointBase* TargetPoint);

	bool PlatformMoveToTatgets(TArray<ATargetPointBase*> Targets, bool bHasRandomMovement);

	








	//VARIABLES






	//DELEGATES















};
