// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatformBase.generated.h"


//FWD Delcarations

class ATargetPointBase;

UENUM(BlueprintType)
enum class EPlatformType : uint8
{
	PT_Default UMETA(DisplayName = "DefaultType")

	,PT_MoveAndStop UMETA(DisplayName = "Move and Stop")

	,PT_Stopping UMETA(DisplayName = "Stopping")

	,PT_Collaborative UMETA(DisplayName = "Collaborative")



	

};


USTRUCT(BlueprintType)

struct FMySparseClassData
{
	GENERATED_BODY()


		FMySparseClassData()
		: nPlatformDefaultName("NAME_None")
		{}

	

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
	FName nDefaultPlatformName_DEPRECATED;

#endif

	//////////////////////////////////



public:

	AMovingPlatformBase();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;



	//PROPERTIES

	


	

	//GETTERS

public:

	UPROPERTY(EditAnywhere, Category = "PlatformBase")
		EPlatformType PlatformType UMETA(DisplayName = "Platform Type");

	//Changes the mode to as if a button would have triggered the current platform
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "PlatformBase")
		bool IsButtonActive;






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


	UFUNCTION(BlueprintPure , Category = "PlatformBase")
		TArray<ATargetPointBase*> GetInitialTargetsReached();


	UFUNCTION(BlueprintPure , Category = "PlatformBase")
	float GetSpeed();


	UFUNCTION(BlueprintCallable, Category = "PlatformBase")
		void SetSpeed(float fNewSpeed);


	UFUNCTION(BlueprintPure, Category = "PlatformBase")
		float GetLastSpeed();


	UFUNCTION(BlueprintCallable, Category = "PlatformBase")
		void SetLastSpeed(float fNewLastSpeed);


	UFUNCTION(BlueprintPure, Category = "PlatformBase")
		bool GetCanMove();


	UFUNCTION(BlueprintCallable, Category = "PlatformBase")
		void SetbCanMove(bool bNewMovementState);

	UFUNCTION(BlueprintPure , Category = "PlatformBase")
	TArray<ATargetPointBase*> GetLastTargetsReached();


	UFUNCTION(BlueprintCallable , Category = "PlatformBase")
	void StopPlatformMovement();


	UFUNCTION(BlueprintCallable , Category ="PlatformBase")
	void  StartPlatformMovement();


	UFUNCTION(BlueprintPure, Category = "PlatformBase")
		TArray<ATargetPointBase*> GetTargetsToReachOnPush();


	UFUNCTION(BlueprintCallable, Category = "PlatformBase")
		void SetTargetsToReachOnPush(TArray<ATargetPointBase*> NewTargets);

	
		










	//FUNCTIONS


	/*Change the targets to reach by the platform based on a button being pushed*/
	UFUNCTION(BlueprintCallable, category = "PlatformBase")
		bool OnControlButtonPushed(bool bIsButtonactive);

	UFUNCTION(BlueprintCallable, Category = "PlatformBase")
		void StartCollaborativeMovement(TArray<ATargetPointBase*>Targets);

	UFUNCTION(BlueprintCallable, Category = "CollaborativePlatform")
		void StartBaseMovement(TArray<ATargetPointBase*>Targets ,  bool bHasRandomMovement);

	UFUNCTION(BlueprintCallable, Category = "PlatformBase")
		void AddSpeed(float fSpeedToadd);

	UFUNCTION(BlueprintCallable , Category = "CollaborativePlatform")
		void AddCollaborativeEffects();

	UFUNCTION(BlueprintCallable, Category = "CollaborativePlatform")
		void RemoveCollaborativeEffects();
	


	bool PlatformGo(ATargetPointBase* TargetPoint);

	bool PlatformMoveToTatgets(TArray<ATargetPointBase*> Targets, bool bHasRandomMovement);

	






	bool bIsReaching = false;

	//VARIABLES






	//DELEGATES

	protected:

		UPROPERTY(BlueprintReadOnly, Category = "CollaborativePlatformBase", meta = (DisplayName = "Is Collaborative"))
			bool bIsCollaborative;

			//Targets that the platform will move between
		UPROPERTY(EditAnywhere, Category = "PlatformBase")
			TArray<ATargetPointBase*>TargetsToReach;

		UPROPERTY(BlueprintReadOnly, Category = "PlatformBase")
			TArray<ATargetPointBase*>LastTargetsReached;

		UPROPERTY(BlueprintReadOnly, Category = "PlatformBase")
			TArray<ATargetPointBase*>InitialTargetsReached;

	private:

	

		

		// If true The Platform will move between the given Targets with a random movement
		UPROPERTY(EditAnywhere, Category = "PlatformBase")
			bool RandomMovementToTargets;

		UPROPERTY(EditAnywhere, Category = "PlatformBase", meta = (DisplayName = "CanMove"))
			bool bCanMove;

		UPROPERTY(EditAnywhere, Category = "PlatformBase", meta = (ClampMin = 0.f), meta = (ClampMax = 500.f), meta = (DisplayName = "Speed"))
			float fSpeed = 50.f;

		




	




		//Targets that the platform will move between when we push a button
		TArray<ATargetPointBase*>TargetsToReachOnButonPush;

		float fLastSpeed;

		

		int32 ArrayCounter = 0;

		ATargetPointBase* InitialTarget;

		ATargetPointBase* LastTarget;

		ATargetPointBase* TargetReaching;

		ATargetPointBase* LastTargetReached;

		bool bIsButtonActivated = false;















};
