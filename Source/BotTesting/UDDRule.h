// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UDDFact.h"
#include "UObject/NoExportTypes.h"
#include "UDDRule.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class BOTTESTING_API UUDDRule : public UObject
{
	GENERATED_BODY()
	

private:
	TArray<UDDFact*> requiredCriteria;
	FString wavKey;
public:
	
	UFUNCTION(BlueprintCallable, Category = "Dynamic Dialogue")
	void Initialize(TArray<UDDFact*> criteria, FString wav) {
		requiredCriteria = criteria;
		wavKey = wav;
	}

	UFUNCTION(BlueprintCallable, Category = "Dynamic Dialogue")
	TArray<UDDFact*> GetCriteria() {
		return requiredCriteria;
	}	
	
	UFUNCTION(BlueprintCallable, Category = "Dynamic Dialogue")
	FString ToString() {
		FString temp = FString("{");
		for (int i = 0; i < requiredCriteria.Num(); i++) {
			temp += requiredCriteria[i]->ToString() + FString(", ");
		}
		temp += FString("}, {") + wavKey + FString("}");
		return temp;
	}

	UFUNCTION(BlueprintCallable, Category = "Dynamic Dialogue")
	int GetMatchValue(const TArray<UDDFact*>& facts) {

		int points = 0;

		for (int i = 0; i < (int)requiredCriteria.Num(); i++) {
			
			bool foundMatch = false;

			for (int j = 0; j < facts.Num(); j++) {

				if (requiredCriteria[i]->Compare(facts[j])) {
					points++;
					foundMatch = true;
				}

			}

			if (foundMatch == false) {
				return -1;
			}

		}

		return points;
	}

	UFUNCTION(BlueprintCallable, Category = "Dynamic Dialogue")
	FString GetWavKey() {
		return wavKey;
	}
};
