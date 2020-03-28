// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMachine/Classes/SM_State.h"


USM_State::USM_State() 
{

	bLoopByDefault = true;

}

USM_State* USM_Branch::TryBranch(const UObject* RefObject, const TArray<USM_InputAtom*>& DataSource, int32 DataIndex, int32& OutDataIndex)
{

	OutDataIndex = DataIndex;

	if (!AcceptableInputs.Num() || (DataSource.IsValidIndex(DataIndex)) && AcceptableInputs.Contains(DataSource[DataIndex])) 
	{
	
		++OutDataIndex;

		return bReverseInputTest ? nullptr : DestinationState;
	
	}
	
	return bReverseInputTest ? DestinationState : nullptr;
}

FStateMachineResult USM_State::RunState(const UObject* RefObject, const TArray<USM_InputAtom*>& DataSource, int32 DataIndex /* = 0 */, int32 RemainingSteps /* = -1*/) 
{

	bool bMustEndNow = (bTerminateImmedietly || !DataSource.IsValidIndex(DataIndex));


	// If we are still running, see where our branches lead.

	if (RemainingSteps && !bMustEndNow) 
	{
		USM_State* DestionationState = nullptr;
		int32 DestionationDataIndex = DataIndex;
		for (int32 i =0; i < InstancedBraches.Num(); i++) 
		{
		
			if (InstancedBraches[i])
			{

				DestionationState = InstancedBraches[i]->TryBranch(RefObject, DataSource, DataIndex, DestionationDataIndex);



				if (DestionationState)
				{


					return DestionationState->RunState(RefObject, DataSource, DestionationDataIndex, RemainingSteps);

				}
			}

			// We didnt find any accpetable branch

			if (bLoopByDefault) 
			{
			
				return LoopState(RefObject, DataSource, DataIndex, RemainingSteps);
			
			}
			bMustEndNow = true;
		
		}


	}

	FStateMachineResult SMR;
	SMR.FinalState = this;
	SMR.DataIndex = DataIndex;
	SMR.CompletionType = bMustEndNow ? CompletionType : EStateMachineCompletionType::OutOfSteps;


	return SMR;


}

FStateMachineResult USM_State::LoopState(const UObject* RefObject, const TArray<USM_InputAtom*>& DataSource, int32 DataIndex, int32 RemainingSteps)
{


// By defalut, increase DataIndex by 1 and decrease Remaining Steps by 1.
	return RunState(RefObject, DataSource, DataIndex + 1, RemainingSteps - 1);

}

