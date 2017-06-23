// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/LevelScriptActor.h"
#include "MainLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class TWOPLAYERGAME_API AMainLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite, Category = "TwoPlayer")
	APlayerController * Player1;
	UPROPERTY(BlueprintReadWrite, Category = "TwoPlayer")
	APlayerController * Player2;
	UPROPERTY(BlueprintReadWrite, Category = "TwoPlayer")
	class ATwoPlayerCharacter* Player1Char;
	UPROPERTY(BlueprintReadWrite, Category = "TwoPlayer")
	class ATwoPlayerCharacter* Player2Char;
};
