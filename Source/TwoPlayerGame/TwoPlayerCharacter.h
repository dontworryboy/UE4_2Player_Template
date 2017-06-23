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

	//�÷��̾��� �̵� ���� �����Լ�
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	//�÷��̾��� ī�޶� ���� �����Լ�
	void TurnRate(float AxisValue);
	void LookupRate(float AxisValue);

	//�÷��̾��� �׼� ���� �Լ�
	void OnAttack();
	void EndAttack();
	void OnJump();
	void EndJump();
	void LockOn();
	void LockOff();

	//�� ĳ���͸� �ٶ󺸰� �Ѵ�.
	UFUNCTION(BlueprintCallable, Category = "Twoplayer")
	void SetLockOnRotation();

	//�ݸ��� �� ���� �Լ�(�������� ȣ��)
	UFUNCTION(BlueprintCallable, Category = "TwoPlayer")
	void SetPlayerCollision(int32 PlayerIndex);
	
private:
	//�� ���� ��������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TwoPlayer", meta = (AllowPrivateAccess = "true"))
		UBoxComponent * LockOnTrigger;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TwoPlayer", meta = (AllowPrivateAccess = "true"))
		UCameraComponent * PlayerCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TwoPlayer", meta = (AllowPrivateAccess = "true"))
		USpringArmComponent * PlayerSpringArm;

public:
	//�е� �潺ƽ ���۰���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TwoPlayer")
	float StickControlSensitivity;

	//�ִϸ��̼� ��Ʈ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TwoPlayer")
	ETwoPlayerState PlayerAnimState;

	//���� �ȿ� ���� ĳ���� �ĺ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TwoPlayer")
	ATwoPlayerCharacter * EnemyCharacter;

	//�� �� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TwoPlayer")
	bool bLockOn;


};
