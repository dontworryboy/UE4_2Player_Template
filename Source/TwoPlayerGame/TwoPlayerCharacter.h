// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"

#include "TwoPlayerGameObject.h"

#include "TwoPlayerCharacter.generated.h"



UCLASS()
class TWOPLAYERGAME_API ATwoPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATwoPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//플레이어의 이동 조작 관련함수
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	//플레이어의 카메라 조작 관련함수
	void TurnRate(float AxisValue);
	void LookupRate(float AxisValue);

	//플레이어의 액션 관련 함수
	void OnAttack();
	void EndAttack();
	void OnJump();
	void EndJump();
	void LockOn();
	void LockOff();

	//적 캐릭터를 바라보게 한다.
	UFUNCTION(BlueprintCallable, Category = "Twoplayer")
	void SetLockOnRotation();

	//콜리전 셋 설정 함수(레벨에서 호출)
	UFUNCTION(BlueprintCallable, Category = "TwoPlayer")
	void SetPlayerCollision(int32 PlayerIndex);
	
private:
	//락 온의 범위설정
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TwoPlayer", meta = (AllowPrivateAccess = "true"))
		UBoxComponent * LockOnTrigger;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TwoPlayer", meta = (AllowPrivateAccess = "true"))
		UCameraComponent * PlayerCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TwoPlayer", meta = (AllowPrivateAccess = "true"))
		USpringArmComponent * PlayerSpringArm;

public:
	//패드 썸스틱 조작감도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TwoPlayer")
	float StickControlSensitivity;

	//애니메이션 컨트롤
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TwoPlayer")
	ETwoPlayerState PlayerAnimState;

	//범위 안에 들어온 캐릭터 식별
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TwoPlayer")
	ATwoPlayerCharacter * EnemyCharacter;

	//락 온 중인지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TwoPlayer")
	bool bLockOn;


};
