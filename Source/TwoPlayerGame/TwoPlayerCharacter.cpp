// Fill out your copyright notice in the Description page of Project Settings.

#include "TwoPlayerGame.h"
#include "Kismet/KismetMathLibrary.h"
#include "TwoPlayerCharacter.h"


// Sets default values
ATwoPlayerCharacter::ATwoPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerAnimState = ETwoPlayerState::IDLE;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> 
		SK_Mesh(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));

	GetMesh()->SetSkeletalMesh(SK_Mesh.Object);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0,-90,0));

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	

	LockOnTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("LockOnRange"));
	LockOnTrigger->SetBoxExtent(FVector(1000, 1000, 500));
	LockOnTrigger->SetRelativeLocation(FVector(0, 0, 0));
	LockOnTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LockOnTrigger->SetupAttachment(RootComponent);
	//GetCapsuleComponent()->SetRelativeLocation(FVector(0, 0, 0));

	PlayerSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	PlayerSpringArm->SetupAttachment(RootComponent);
	PlayerSpringArm->TargetArmLength = 300.0f;
	PlayerSpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	PlayerSpringArm->bDoCollisionTest = false;
	//PlayerSpringArm->SetRelativeLocation(FVector(0, 0, 0));

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	PlayerCamera->SetupAttachment(PlayerSpringArm);
	PlayerCamera->bUsePawnControlRotation = false;

	EnemyCharacter = nullptr;

	StickControlSensitivity = 45.0f;
	bLockOn = false;
}

// Called when the game starts or when spawned
void ATwoPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogClass, Warning, TEXT("%s, %d"), TEXT("CharacterBeginPlay"), GetController()->PlayerState->PlayerId);
}

// Called every frame
void ATwoPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bLockOn)
	{
		SetLockOnRotation();
	}

}

// Called to bind functionality to input
void ATwoPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATwoPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATwoPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("TurnRate", this, &ATwoPlayerCharacter::TurnRate);
	PlayerInputComponent->BindAxis("LookupRate", this, &ATwoPlayerCharacter::LookupRate);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ATwoPlayerCharacter::OnJump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ATwoPlayerCharacter::EndJump);
	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &ATwoPlayerCharacter::OnAttack);
	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Released, this, &ATwoPlayerCharacter::EndAttack);
	PlayerInputComponent->BindAction("LockOn", EInputEvent::IE_Pressed, this, &ATwoPlayerCharacter::LockOn);
	PlayerInputComponent->BindAction("LockOn", EInputEvent::IE_Released, this, &ATwoPlayerCharacter::LockOff);
}

void ATwoPlayerCharacter::MoveForward(float AxisValue)
{
	//UE_LOG(LogClass, Warning, TEXT("%f"), AxisValue);
	FRotator CurrentYawRotation(0, GetControlRotation().Yaw, 0);
	AddMovementInput(UKismetMathLibrary::GetForwardVector(CurrentYawRotation), AxisValue);
	
}

void ATwoPlayerCharacter::MoveRight(float AxisValue)
{
	//UE_LOG(LogClass, Warning, TEXT("%f"), AxisValue);
	FRotator CurrentYawRotation(0, GetControlRotation().Yaw, 0);
	AddMovementInput(UKismetMathLibrary::GetRightVector(CurrentYawRotation), AxisValue);
}

void ATwoPlayerCharacter::TurnRate(float AxisValue)
{
	//UE_LOG(LogClass, Warning, TEXT("%f"), AxisValue);
	AddControllerYawInput(StickControlSensitivity * GetWorld()->GetDeltaSeconds() * AxisValue);
}

void ATwoPlayerCharacter::LookupRate(float AxisValue)
{
	//UE_LOG(LogClass, Warning, TEXT("%f"), AxisValue);
	AddControllerPitchInput(StickControlSensitivity * GetWorld()->GetDeltaSeconds() * AxisValue);
}

void ATwoPlayerCharacter::OnAttack()
{
	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("AttackStart"));

}

void ATwoPlayerCharacter::EndAttack()
{
	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("AttackEnd"));

}

void ATwoPlayerCharacter::OnJump()
{
	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("JumpStart"));

}
void ATwoPlayerCharacter::EndJump()
{
	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("JumpEnd"));

}

void ATwoPlayerCharacter::LockOn()
{
	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("LockOn"));
	bLockOn = true;
}

void ATwoPlayerCharacter::LockOff()
{
	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("LockOff"));
	bLockOn = false;
}

void ATwoPlayerCharacter::SetLockOnRotation()
{
	TArray<AActor*> OverlappingActors;
	LockOnTrigger->GetOverlappingActors(OverlappingActors);

	for (auto OverlappedActors : OverlappingActors)
	{
		EnemyCharacter = Cast<ATwoPlayerCharacter>(OverlappedActors);

		if (EnemyCharacter)
		{
			if (EnemyCharacter->PlayerState->PlayerId != this->PlayerState->PlayerId)
			{
				UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("overlapped"));
				FRotator EnemyDirection = 
					UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), EnemyCharacter->GetActorLocation());

				SetActorRotation(EnemyDirection);
			}
		}
	}
}

void ATwoPlayerCharacter::SetPlayerCollision(int32 PlayerIndex)
{
	switch (PlayerIndex)
	{
	case 0:
		LockOnTrigger->SetCollisionProfileName(TEXT("Player1TriggerSet"));
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player1Set"));
		break;

	case 1:
		LockOnTrigger->SetCollisionProfileName(TEXT("Player2TriggerSet"));
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player2Set"));
		break;

	default:
		return;

	}
	int32 Index = GetController()->PlayerState->PlayerId;
	UE_LOG(LogClass, Warning, TEXT("%s, %d"), TEXT("setplayerCollisionCalled"), GetController()->PlayerState->PlayerId);
}