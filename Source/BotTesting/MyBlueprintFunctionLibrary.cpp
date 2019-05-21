// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "BotTesting/UDDRule.h"
#include "BotTesting/UDDFact.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine.h"


int UMyBlueprintFunctionLibrary::GetActorUniqueID(AActor* Actor) {
	return (int)Actor->GetUniqueID();
}

void UMyBlueprintFunctionLibrary::SaveRules(FString filename, UPARAM(ref) TArray<UUDDRule*>& InRules) {
	FString ruleFile = FPaths::GameContentDir() + "dialogueFiles/dialogue.dat";

	//UE_LOG(None, Warning, TEXT("Saving file: %s"), *ruleFile);

	TArray<FString> textEntries;

	for (int i = 0; i < InRules.Num(); i++) {

		UUDDRule* rule = InRules[i];

		/*
		textEntries.Add("\t" + de.who);
		textEntries.Add("\t" + de.concept);
		textEntries.Add("\t" + de.wav);
		*/
		textEntries.Add("{");

		textEntries.Add("\t" + rule->GetCriteria()[0]->GetValue().ToString());

		textEntries.Add("\t" + rule->GetCriteria()[1]->GetValue().ToString());

		textEntries.Add("\t" + rule->GetWavKey());

		for (int i = 3; i < rule->GetCriteria().Num(); i++) {
			textEntries.Add("\t" + rule->GetCriteria()[i]->ToString());
		}


		textEntries.Add("}");
	}

	FFileHelper::SaveStringArrayToFile(textEntries, *ruleFile);


}

void UMyBlueprintFunctionLibrary::SaveStringsToFile(UPARAM(ref) TArray<FString>& strings, FString fileName) {
	FString file = FPaths::GameContentDir() + "miscfiles/" + fileName;
	FFileHelper::SaveStringArrayToFile(strings, *file);
}

void UMyBlueprintFunctionLibrary::LoadStringsFromFile(TArray<FString>& strings, FString fileName) {
	FString file = FPaths::GameContentDir() + "miscFiles/" + fileName;

	if (!FFileHelper::LoadANSITextFileToStrings(*file, &IFileManager::Get(), strings)) {
		UE_LOG(LogTemp, Warning, TEXT("Unable to succesfully load rule file: %s"), *file);
		return;
	}
}

void UMyBlueprintFunctionLibrary::ParseRules(UObject* Outer, FString filename, TArray<UUDDRule*>& OutRules)
{
	TArray<FString> inFile;

	//if (ruleFile == "") {
	FString ruleFile = FPaths::GameContentDir() + "dialogueFiles/dialogue.dat";
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

			UDDFact* newFact = NewObject<UDDFact>(Outer);
			newFact->Initialize(FName("who"), FName(*who));
			newFacts.Add(newFact);

			newFact = NewObject<UDDFact>(Outer);
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

				newFact = NewObject<UDDFact>(Outer);
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

	OutRules = newRules;




}
