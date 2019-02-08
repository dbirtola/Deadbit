// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "UDDRule.h"
#include "UDynamicDialogueManagerBase.generated.h"


UCLASS()
class BOTTESTING_API AUDynamicDialogueManagerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUDynamicDialogueManagerBase();

protected:
	UPROPERTY(BlueprintReadWrite)
	TArray<UUDDRule*> rules;
	UPROPERTY(BlueprintReadWrite)
	FString ruleFile;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

	void LoadDialogueFile(FString fileName) {
		TArray<FString> inFile;

		//if (ruleFile == "") {
		ruleFile = FPaths::GameContentDir() + "dialogueFiles/dialogue.dat";
			//return;
		//}

		if (!FFileHelper::LoadANSITextFileToStrings(*ruleFile, &IFileManager::Get(), inFile)) {
			UE_LOG(LogTemp, Warning, TEXT("Unable to succesfully load rule file: %s"), *ruleFile);
			return;
		}

		for (int i = 0; i < inFile.Num(); i++) {
			inFile[i].Trim();
		}

		//rules.Empty();
		TArray<UUDDRule*> newRules;
		TQueue<FString> entryQueue;
		UE_LOG(LogTemp, Warning, TEXT("Started %s"), *ruleFile);

		for (int i = 0; i < inFile.Num(); i++) {




			//End of entry block
			if (inFile[i] == "}") {

				entryQueue.Pop(); //remove the {
				FString who, concept, wav;
				TArray<FString> criteria;
				FString thisCrit;

				entryQueue.Dequeue(who);
				entryQueue.Dequeue(concept);
				entryQueue.Dequeue(wav);

				UUDDRule* newRule = NewObject<UUDDRule>();
				
				TArray<UDDFact*> newFacts;
				UDDFact* newFact = NewObject<UDDFact>(this);
				newFact->Initialize(FName("who"), FName(*who));
				newFacts.Add(newFact);

				newFact = NewObject<UDDFact>(this);
				newFact->Initialize(FName("concept"), FName(*concept));
				newFacts.Add(newFact);


				while (entryQueue.Dequeue(thisCrit)) {
					UE_LOG(LogTemp, Warning, TEXT("Adding new criteria %s"), *thisCrit);
					if (thisCrit.IsEmpty()) {
						continue;
					}
					criteria.Add(thisCrit);				
					FString left, right;
					thisCrit.Split(TEXT(":"), &left, &right);
					
					newFact = NewObject<UDDFact>(this);
					newFact->Initialize(FName(*left), FName(*right));
					
					newFacts.Add(newFact);
					

				}
				

				newRule->Initialize(newFacts, wav);
				newRules.Add(newRule);

				UE_LOG(LogTemp, Warning, TEXT("Adding new rule %s"), *newRule->ToString());
				//AddDialogueEntry(concept, who, criteria);

			}
			else {
				entryQueue.Enqueue(inFile[i]);
			}

		}
		UE_LOG(LogTemp, Warning, TEXT("Finished loading rule file: %s"), *ruleFile);

		rules = newRules;
	}
	
};
