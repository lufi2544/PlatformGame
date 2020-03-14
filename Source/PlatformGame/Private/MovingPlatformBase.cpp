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
	return bIsCollaborative;

}


void AMovingPlatformBase::SetIscollaborative(bool b)
{
	bIsCollaborative = b;
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

	if (TargetsToReach.Num() > 0) 
	{
		LastTargetsReached = TargetsToReach;

		TargetsToReach = NewTargets;
	
	}
	
}

bool AMovingPlatformBase::GetCanMove()
{
	return bCanMove;
}

void AMovingPlatformBase::SetbCanMove(bool bNewMovementState)
{

	bCanMove = bNewMovementState;

}

TArray<ATargetPointBase*> AMovingPlatformBase::GetLastTargetsReached()
{
	return LastTargetsReached;
}

void AMovingPlatformBase::StopPlatformMovement()
{
	bCanMove = false;
}

void AMovingPlatformBase::StartPlatformMovement()
{
	bCanMove = true;
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
		if (!bIsCollaborative) 
		{
		
			StartBaseMovement(Targets, bHasRandomMovement);
		
		}
		else
		{

			StartCollaborativeMovement(Targets);
		}
	
	
	}
	else
	{
		bSuccess = false;

		UE_LOG(LogTemp , Error, TEXT("The Targets number is < 0"));
	}
	
	return bSuccess;
}


bool AMovingPlatformBase::OnControlButtonPushed(bool bIsButtonActive)
{

	IsButtonActive = bIsButtonActive;

	return IsButtonActive;
}



void AMovingPlatformBase::StartCollaborativeMovement(TArray<ATargetPointBase*>Targets)
{

	bool bSuccess = false;

	if (!bIsReaching)
	{
		if (!ensure(Targets[ArrayCounter])) { return ; }

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





void AMovingPlatformBase::StartBaseMovement(TArray<ATargetPointBase*>Targets, bool bHasRandomMovement)
{
	bool bSuccess = false;

	
	
		if (!bHasRandomMovement)
		{

			if (!bIsReaching)
			{
				if (!ensure(Targets[ArrayCounter])) { return ; }

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

				if (!ensure(Targets[ArrayCounter])) { return ; }

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


		SparseClassData->nPlatformDefaultName = nDefaultPlatformName_DEPRECATED;


#endif

}


#endif