// Fill out your copyright notice in the Description page of Project Settings.

#include "Bits.h"

// Sets default values
ABits::ABits()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABits::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABits::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABits::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

