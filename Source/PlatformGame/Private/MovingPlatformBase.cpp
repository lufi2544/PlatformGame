// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatformBase.h"

#include "TargetPointBase.h"
#include "Engine/World.h"
#include "Engine/BlueprintGeneratedClass.h"

AMovingPlatformBase::AMovingPlatformBase() 
{

	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);

	bCanMove = true;

	

}

void AMovingPlatformBase::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	

	if (HasAuthority())
	{
		if (bCanMove)
		{
			if (!IsButtonActive)
			{

				PlatformMoveToTatgets(TargetsToReach, RandomMovementToTargets);
			}
			else
			{
				PlatformMoveToTatgets(TargetsToReachOnButonPush, RandomMovementToTargets);
			}
		}
		else
		{
		
		}
	}
}

void AMovingPlatformBase::BeginPlay()
{

	Super::BeginPlay();



	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}



}

//GETTERS


bool AMovingPlatformBase::GetIsCollaborativeState() 
{
	//SPARSEDATA PROPERTY
	return GetIsCollaborative();

}




bool AMovingPlatformBase::GetIsButtonActivated()
{
	return bIsButtonActivated;
}

void AMovingPlatformBase::SetIsButtonActivated(bool bNewState)
{

	bIsButtonActivated = bNewState;



}

TArray<ATargetPointBase*> AMovingPlatformBase::GetTargetsToReach()
{
	return TargetsToReach;
}

void AMovingPlatformBase::SetTargetsToReach(TArray<ATargetPointBase*> NewTargets)
{

	TargetsToReach = NewTargets;
}

bool AMovingPlatformBase::GetCanMove()
{
	return bCanMove;
}

void AMovingPlatformBase::SetbCanMove(bool bNewMovementState)
{

	bCanMove = bNewMovementState;

}

TArray<ATargetPointBase*> AMovingPlatformBase::GetTargetsToReachOnPush()
{
	return TargetsToReachOnButonPush;
}

void AMovingPlatformBase::SetTargetsToReachOnPush(TArray<ATargetPointBase*> NewTargets)
{
	TargetsToReachOnButonPush = NewTargets;
}

//FUNCTIONS



bool AMovingPlatformBase::PlatformGo(ATargetPointBase* TargetPointA)
{
	bool bHasReached = false;

	FVector vCurrentActorLocation = GetActorLocation();

	FVector vTarget1Location = TargetPointA->GetActorLocation();

	FVector nvDistanceToTargetPointA = (vTarget1Location - vCurrentActorLocation).GetSafeNormal();

	FVector vLocationToReach = nvDistanceToTargetPointA * vTarget1Location;




	SetActorLocation(vCurrentActorLocation + nvDistanceToTargetPointA * fSpeed * GetWorld()->GetDeltaSeconds());

	if (GetActorLocation().Equals(vTarget1Location, 5.f))
	{

		bHasReached = true;

	}

	

	return bHasReached;
}




bool AMovingPlatformBase::PlatformMoveToTatgets(TArray<ATargetPointBase*> Targets, bool bHasRandomMovement)
{
	bool bSuccess = false;


	if (Targets.Num() > 0)
	{
		if (!GetIsCollaborative()) 
		{
			if (!bHasRandomMovement)
			{

				if (!bIsReaching)
				{
					if (!ensure(Targets[ArrayCounter])) { return false; }

					TargetReaching = Targets[ArrayCounter];

					bIsReaching = true;

				}
				else
				{
					PlatformGo(TargetReaching);

					if (PlatformGo(TargetReaching))
					{
						bSuccess = true;
						bIsReaching = false;

						ArrayCounter++;

						if (ArrayCounter == Targets.Num())
						{

							ArrayCounter = 0;

						}


					}


				}


			}
			else
			{

				if (!bIsReaching)
				{

					ArrayCounter = FMath::RandRange(0, Targets.Num() - 1);

					if (!ensure(Targets[ArrayCounter])) { return false; }

					TargetReaching = Targets[ArrayCounter];

					bIsReaching = true;

				}
				else
				{

					if (TargetReaching != LastTargetReached)
					{
						PlatformGo(TargetReaching);

						if (PlatformGo(TargetReaching))
						{
							LastTargetReached = TargetReaching;
							bIsReaching = false;
							bSuccess = true;

						}

					}
					else
					{
						bIsReaching = false;
						bSuccess = false;

					}


				}



			}
		}
		else
		{

			if (!bIsReaching)
			{
				if (!ensure(Targets[ArrayCounter])) { return false; }

				InitialTarget = Targets[0];

				LastTarget = Targets[Targets.Num() - 1];

				bIsReaching = true;

				TargetReaching = Targets[ArrayCounter];



			}
			else
			{
				if (bIsButtonActivated)
				{
					bCanMove = true;

					PlatformGo(TargetReaching);


					if (PlatformGo(TargetReaching))
					{
						LastTargetReached = TargetReaching;
						bSuccess = true;

						bIsReaching = false;

						ArrayCounter++;

						if (TargetReaching == LastTarget)
						{

							bCanMove = false;
							ArrayCounter = 0;
						}


					}

				}
				else
				{

					bCanMove = true;
					PlatformGo(InitialTarget);




					if (PlatformGo(InitialTarget))
					{
						bCanMove = false;
						LastTargetReached = InitialTarget;
						

					}


				}




			}

		}
	
}
else
	{
	bSuccess = false;
	}

	return bSuccess;
}


bool AMovingPlatformBase::OnControlButtonPushed(bool bIsButtonActive)
{

	IsButtonActive = bIsButtonActive;

	return IsButtonActive;
}



//DELEGATES

//SPARSEDATA


#if WITH_EDITOR

void AMovingPlatformBase::MoveDataToSparseClassDataStruct() const
{

	UBlueprintGeneratedClass* BPClass = Cast<UBlueprintGeneratedClass>(GetClass());

	if (BPClass == nullptr || BPClass->bIsSparseClassDataSerializable == true)
	{
		return;
	}

	Super::MoveDataToSparseClassDataStruct();


#if WITH_EDITORONLY_DATA

		FMySparseClassData* SparseClassData = GetMySparseClassData();


		SparseClassData->bIsCollaborative = bIsCollaborative_DEPRECATED;

		SparseClassData->nPlatformDefaultName = nDefaultPlatformName_DEPRECATED;


#endif

}


#endif