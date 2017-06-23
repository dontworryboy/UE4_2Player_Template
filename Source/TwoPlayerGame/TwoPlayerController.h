// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TwoPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TWOPLAYERGAME_API ATwoPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	
	class ATwoPlayerCharacter * OwnerCharacter;
	
	
};
