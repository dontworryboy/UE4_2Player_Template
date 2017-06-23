// Fill out your copyright notice in the Description page of Project Settings.

#include "TwoPlayerGame.h"

#include "TwoPlayerCharacter.h"

#include "MainLevelScriptActor.h"

void AMainLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	//1p컨트롤러 로드
	Player1 = GetWorld()->GetFirstPlayerController();
	UE_LOG(LogClass, Warning, TEXT("%s, %d"), TEXT("player1"), Player1->PlayerState->PlayerId);
	//1p캐릭터 로드
	Player1Char = Cast<ATwoPlayerCharacter>(Player1->GetCharacter());
	//1p콜리더 셋
	Player1Char->SetPlayerCollision(0);

	//2p컨트롤러 로드
	Player2 = UGameplayStatics::CreatePlayer(GetWorld());
	UE_LOG(LogClass, Warning, TEXT("%s, %d"), TEXT("player2"), Player2->PlayerState->PlayerId);
	//2p캐릭터 로드
	Player2Char = Cast<ATwoPlayerCharacter>(Player2->GetCharacter());
	//2p콜리더 셋
	Player2Char->SetPlayerCollision(1);
}


