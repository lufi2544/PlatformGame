// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Quest.generated.h"

UENUM()
enum class EQuestCompletion : uint8 
{
EQC_NotStarted ,
EQC_Started , 
EQC_Succeded ,
EQC_Failed


};

/**
 * 
 */
UCLASS()
class PLATFORMGAME_API UQuest : public UDataAsset
{
	GENERATED_BODY()
	
};
