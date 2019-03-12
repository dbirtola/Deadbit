// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomFunctions.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CustomFunctions.generated.h"
#include "GameFramework/Actor.h"


void UCustomFunctions::CallState(char functionName[], AActor Player) {
	const FString test = functionName;
	FStringOutputDevice ar;
	Player.CallFunctionByNameWithArguments(*test, ar, NULL, true);
}
