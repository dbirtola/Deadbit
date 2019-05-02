// Fill out your copyright notice in the Description page of Project Settings.


#include "CB_PlayerControllerBase.h"
#include "GameFramework/Pawn.h"


void ACB_PlayerControllerBase::SavePlayerState() {

	FBufferArchive ToBinary;
	ToBinary << GetPawn()->GetActorLocation();
	

	return;
}