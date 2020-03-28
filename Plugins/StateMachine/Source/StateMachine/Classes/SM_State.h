// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SM_State.generated.h"

class USM_Branch;
class USM_State;



UENUM()
enum class EStateMachineCompletionType : uint8
{
	//Implicit failure - this state is not marked as Accepted
	NotAccepted,

	// Succes -  this state is an Accepted state
	Accepted,

	//Explicit failure - this state is specifically marked as failure/not-accept.
	Rejected,

	//Our simulation ran out of steps while the machine was still running.
	OutOfSteps UMETA(Hidden)


};




USTRUCT(Blueprintable)
struct STATEMACHINE_API FStateMachineResult 
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	EStateMachineCompletionType CompletionType;

	UPROPERTY()
	USM_State* FinalState;

	UPROPERTY()
	int32 DataIndex;

};


UCLASS()
class STATEMACHINE_API USM_InputAtom  : public UDataAsset// (ATOMIC) this is the minimum piece of info, one leter one number, etc. (a ,c ,f,v,s,), jut one.
{
	GENERATED_BODY()

public:


	//Display value for this input atom, mainly for debugging purposes
	UPROPERTY(EditAnywhere)
	FName Description;


};


UCLASS(EditInLineNew)
class STATEMACHINE_API USM_Branch : public UDataAsset
{
	GENERATED_BODY()



public:
	/*Returns DestinationState on Success , NULL on failure. For Subclasses,
	OutDataIndex might be something other than 1, if a branch is made to consume multiple inputs*/
	virtual USM_State* TryBranch(const UObject* RefObject, const TArray<USM_InputAtom*>& DataSource, int32 DataIndex, int32& OutDataIndex);

protected:
	//State where we will go next if this branch is taken, If null, this branch will be ignored.
	UPROPERTY(EditANywhere)
		USM_State* DestinationState;

	//If true, the meaning of AcceptableInputs is reserved.
	UPROPERTY(EditAnywhere)
		uint32 bReverseInputTest : 1;

	//Acceptable inputs. The current input atom must be on this list
	UPROPERTY(EditAnywhere)
		TArray<USM_InputAtom*>AcceptableInputs;

};


/**
 *
 */
UCLASS()
class STATEMACHINE_API USM_State : public UDataAsset
{
	GENERATED_BODY()

public:

	USM_State();

	/*Attempt to run the state with input from the given DataSource object.
	Will Start reading inpuit at DataIndex.
	Will decrement RemainingSteps and automatically fail after it hits 0.

	*/
	UFUNCTION(BlueprintCallable, Category = "State Machine")
	virtual FStateMachineResult RunState(const UObject* RefObject, const TArray<USM_InputAtom*>& dataSource, int32 DataIndex = 0, int32 RemainingSteps = -1); // -1 is 4 billions .Practicaly infinite

	

protected:

	/* Loop . Used whren input atom being processed isn`t recognize */
	virtual FStateMachineResult LoopState(const UObject* RefObject, const TArray<USM_InputAtom*>& DataSource, int32 DataIndex, int32 RemainigSteps);

	/* If input runs out on this rate state (or TerminateImmediately is true) , this is hiow the result will be interpreted. */
	UPROPERTY(EditAnywhere)
		EStateMachineCompletionType CompletionType;

	//A state machine run that enters this state will terminate immedietly.
	UPROPERTY(EditAnywhere)
		uint32 bTerminateImmedietly : 1;

	//If this is set, this state will loop on itself whenwver an unhandled input atosm is detected
	UPROPERTY(EditAnywhere)
		uint32 bLoopByDefault : 1;

	//Branches to other states. PriorityOrder , so the first successful branch will be taken.
	UPROPERTY(EditAnywhere, Instanced)
		TArray<USM_Branch*> InstancedBraches;


};