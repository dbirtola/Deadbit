// Fill out your copyright notice in the Description page of Project Settings.

#include "UDynamicDialogueManagerBase.h"


// Sets default values
AUDynamicDialogueManagerBase::AUDynamicDialogueManagerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUDynamicDialogueManagerBase::BeginPlay()
{
	Super::BeginPlay();

	LoadDialogueFile(ruleFile);

	
}

// Called every frame
void AUDynamicDialogueManagerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

