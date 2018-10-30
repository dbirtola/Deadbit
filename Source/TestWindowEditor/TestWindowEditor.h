
#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "UnrealEd.h"


#include "../../../../../Engine/Source/Editor/LevelEditor/Public/LevelEditor.h"
#include "../../../../../Engine/Source/Runtime/Slate/Public/Framework/MultiBox/MultiBoxBuilder.h"
#include "../../../../../Engine/Source/Runtime/Core/Public/Templates/SharedPointer.h"

#include "../../../../../Engine/Source/Runtime/Slate/Public/Framework/Commands/UICommandList.h"

DECLARE_LOG_CATEGORY_EXTERN(TestWindowEditor, All, All)

class DialogueEntry {



public:

	FString concept;
	FString who;
	FString wav;
	TArray<FString> criteria;

	DialogueEntry(FString concept, FString who, FString wav, TArray<FString> criteria) {
		this->concept = concept;
		this->who = who;
		this->wav = wav;
		this->criteria = criteria;
	}

	FString GetConcept() { return concept; }
	FString GetWho() { return who; }
	FString GetWav() { return wav; }
	TArray<FString> GetCriteria() { return criteria; }

	FString ToString() {

		FString crit = FString("");
		for (int i = 0; i < criteria.Num(); i++) {
			crit += "<" + criteria[i] + ">";
		}


		return FString("[Concept: " + concept + "] " + "[Who: " + who + " ] - " + crit);

	}

};

class FTestWindowEditorModule: public IModuleInterface {

private:



public:

	static FTestWindowEditorModule* instance;

	virtual void StartupModule() override;
	

	virtual void ShutdownModule() override;

	static void CreateWindow();

	static FReply TestClick();

	static void TextChanged(const FText& inText);
	static void WavTextChanged(const FText& inText);

	static void OnChangeConcept(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo);

	static void OnChangeWho(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo);


	static FReply TestSave();

	static FString currentString;
	static FString currentConcept;
	static FString currentWho;
	static FString currentWav;

	static TArray<TSharedPtr<FString>> *whoOptions;
	static TArray<TSharedPtr<FString>> *conceptOptions;

	

	static TArray<TSharedPtr<DialogueEntry>> dialogueEntries;


	static TSharedPtr<SListView<TSharedPtr<DialogueEntry>>> dialogueList;

	static DialogueEntry AddDialogueEntry(FString concept, FString who, FString wav, TArray<FString> criteria);

	static TSharedRef<ITableRow> OnGenerateWidgetForList(TSharedPtr<DialogueEntry> InItem, const TSharedRef<STableViewBase>& OwnerTable);

	static void SaveEntries(FString fileName);

	static void LoadEntries(FString fileName);


};