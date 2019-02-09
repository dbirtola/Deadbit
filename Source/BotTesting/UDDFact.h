// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <string>
#include "UDDFact.generated.h"
/**
 * 
 */

UCLASS(BlueprintType)
class BOTTESTING_API UDDFact : public UObject
{

	GENERATED_BODY()
private:
		//int64* key = 0;
		//int64* value = 0;

	FName key;
	FName value;
public:
	UDDFact();
	//UDDFact(FString key, FString value);

	UDDFact(FName key, FName value);
	~UDDFact();

	UFUNCTION(BlueprintCallable, Category = "Dyanmic Dialogue")
	FName GetKey() {
		return key;
	}

	UFUNCTION(BlueprintCallable, Category = "Dyanmic Dialogue")
	FName GetValue() {
		return value;
	}

	UFUNCTION(BlueprintCallable, Category = "Dyanmic Dialogue")
	FString ToString() {
		return key.ToString() + FString(": ") + value.ToString();
	}

	UFUNCTION(BlueprintCallable, Category = "Dynamic Dialogue")
	bool Compare(UDDFact* f2);

	UFUNCTION(BlueprintCallable, Category = "Dynamic Dialogue")
	bool Initialize(FName fkey, FName fvalue);
	//bool Initialize(FString fkey, FString fvalue);


};


