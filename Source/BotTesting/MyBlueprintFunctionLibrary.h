// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class BOTTESTING_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Dynamic Dialogue")
	static void ParseRules(UObject* Outer, FString filename, TArray<UUDDRule*>& OutRules);

	UFUNCTION(BlueprintCallable, Category = "Dynamic Dialogue")
	static void SaveRules(FString filename, UPARAM(ref) TArray<UUDDRule*>& InRules);

	UFUNCTION(BlueprintCallable, Category = "File Management")
	static void SaveStringsToFile(UPARAM(ref) TArray<FString>& strings, FString fileName);

	UFUNCTION(BlueprintCallable, Category = "File Management")
	static void LoadStringsFromFile(TArray<FString>& strings, FString fileName);

};
