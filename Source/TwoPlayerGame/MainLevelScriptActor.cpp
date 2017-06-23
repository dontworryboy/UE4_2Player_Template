// Fill out your copyright notice in the Description page of Project Settings.

#include "TwoPlayerGame.h"

#include "TwoPlayerCharacter.h"

#include "MainLevelScriptActor.h"

void AMainLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	//1p��Ʈ�ѷ� �ε�
	Player1 = GetWorld()->GetFirstPlayerController();
	UE_LOG(LogClass, Warning, TEXT("%s, %d"), TEXT("player1"), Player1->PlayerState->PlayerId);
	//1pĳ���� �ε�
	Player1Char = Cast<ATwoPlayerCharacter>(Player1->GetCharacter());
	//1p�ݸ��� ��
	Player1Char->SetPlayerCollision(0);

	//2p��Ʈ�ѷ� �ε�
	Player2 = UGameplayStatics::CreatePlayer(GetWorld());
	UE_LOG(LogClass, Warning, TEXT("%s, %d"), TEXT("player2"), Player2->PlayerState->PlayerId);
	//2pĳ���� �ε�
	Player2Char = Cast<ATwoPlayerCharacter>(Player2->GetCharacter());
	//2p�ݸ��� ��
	Player2Char->SetPlayerCollision(1);
}


