// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CustomFunctions.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BOTTESTING_API UCustomFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
private:
public:
	UFUNCTION(BlueprintCallable, Category = "Function")
		void CallState(char functionName[], AActor Player);
};
