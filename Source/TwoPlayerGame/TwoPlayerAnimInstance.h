// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"

#include "TwoPlayerGameObject.h"

#include "TwoPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TWOPLAYERGAME_API UTwoPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public://������
	UTwoPlayerAnimInstance();

public://����Լ�


public://�������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TwoPlayer")
	ETwoPlayerState CurrentState;
	
};
