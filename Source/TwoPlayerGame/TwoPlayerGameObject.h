// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "TwoPlayerGameObject.generated.h"

/**
 * 


 */

UENUM(BlueprintType)
enum class ETwoPlayerState : uint8
{
	IDLE,
	ATTACK,
	JUMP,
	DASH
};

UCLASS()
class TWOPLAYERGAME_API UTwoPlayerGameObject : public UObject
{
	GENERATED_BODY()
	
	
	
	
};
