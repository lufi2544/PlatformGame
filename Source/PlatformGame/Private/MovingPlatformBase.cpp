// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatformBase.h"

#include "TargetPointBase.h"

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












//FUNCTIONS



bool AMovingPlatformBase::PlatformGo(ATargetPointBase* TargetPointA)
{
	bool bHasReached = false;

	FVector vCurrentActorLocation = GetActorLocation();

	FVector vTarget1Location = TargetPointA->GetActorLocation();

	FVector nvDistanceToTargetPointA = (vTarget1Location - vCurrentActorLocation).GetSafeNormal();

	FVector vLocationToReach = nvDistanceToTargetPointA * vTarget1Location;




	SetActorLocation(vCurrentActorLocation + nvDistanceToTargetPointA * fSpeed);

	if (GetActorLocation().Equals(vTarget1Location, 2.f))
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

		if (!bHasRandomMovement)
		{

			if (!bIsReaching)
			{
				if (!ensure(Targets[ArrayCounter])) { return false; }

				PlatformReaching = Targets[ArrayCounter];

				bIsReaching = true;

			}
			else
			{
				PlatformGo(PlatformReaching);

				if (PlatformGo(PlatformReaching))
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

				PlatformReaching = Targets[ArrayCounter];

				bIsReaching = true;
			}
			else
			{

				if (PlatformReaching != LastPlatformReached)
				{
					PlatformGo(PlatformReaching);

					if (PlatformGo(PlatformReaching))
					{
						LastPlatformReached = PlatformReaching;
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