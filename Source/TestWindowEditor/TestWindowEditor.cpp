
#include "TestWindowEditor.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"
#include "LevelEditor.h"
#include "PropertyEditorModule.h"
#include "Runtime/Slate/Public/Widgets/Input/STextComboBox.h"

#if WITH_EDITOR
#include "EditorStyleSet.h"
#endif // WITH_EDITOR

IMPLEMENT_GAME_MODULE(FTestWindowEditorModule, TestWindowEditorModule);

DEFINE_LOG_CATEGORY(TestWindowEditor)

#define LLOCTEXT_NAMESCAPE "TestWindowEditor"


FTestWindowEditorModule* FTestWindowEditorModule::instance;



FString FTestWindowEditorModule::currentString;
FString FTestWindowEditorModule::currentWav;
FString FTestWindowEditorModule::currentConcept;
FString FTestWindowEditorModule::currentWho;
TSharedPtr<SListView<TSharedPtr<DialogueEntry>>> FTestWindowEditorModule::dialogueList;


TArray<TSharedPtr<DialogueEntry>> FTestWindowEditorModule::dialogueEntries;

TArray<TSharedPtr<FString>> *FTestWindowEditorModule::whoOptions;
TArray<TSharedPtr<FString>> *FTestWindowEditorModule::conceptOptions;


void FTestWindowEditorModule::StartupModule() {
	UE_LOG(TestWindowEditor, Warning, TEXT("TestWindowEditor: Log Started")); 
	instance = this;
	
	TSharedPtr<FUICommandList> CommandList;

	CommandList = MakeShareable(new FUICommandList);
	
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	struct Local {

		
		static void AddMenuCommands(FMenuBuilder& MenuBuilder) {
			FString FriendlyName = "Please Work";
			FUIAction Action = FExecuteAction::CreateStatic(&FTestWindowEditorModule::CreateWindow);


			MenuBuilder.AddMenuEntry(
				FText::FromString("Fuzzy Dialogue Editor"),
				FText::FromString("Doesn't work yet."),
				FSlateIcon(),
				Action);
		}
		
	};

	
	TSharedRef<FExtender> MenuExtender(new FExtender());
	MenuExtender->AddMenuExtension(
		"EditMain",
		EExtensionHook::After,
		CommandList.ToSharedRef(),
		FMenuExtensionDelegate::CreateStatic(&Local::AddMenuCommands));

	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);

}

void FTestWindowEditorModule::CreateWindow() {

	UE_LOG(TestWindowEditor, Warning, TEXT("Clicked"));

	whoOptions = new TArray<TSharedPtr<FString>>;
	whoOptions->Add(TSharedPtr<FString>(new FString("Moose")));
	whoOptions->Add(TSharedPtr<FString>(new FString("Bot1")));
	whoOptions->Add(TSharedPtr<FString>(new FString("Bot2")));

	conceptOptions = new TArray<TSharedPtr<FString>>;
	conceptOptions->Add(TSharedPtr<FString>(new FString("Static")));
	conceptOptions->Add(TSharedPtr<FString>(new FString("OnSeen")));
	conceptOptions->Add(TSharedPtr<FString>(new FString("OnHit")));	

	//dialogueEntries = TArray<DialogueEntry>();
	TArray<FString> testarr;
	//AddDialogueEntry("Test1", "Test2", testarr);
	LoadEntries(FPaths::GameContentDir() + "dialogueFiles/dialogue.dat");


	auto window = SNew(SWindow).ClientSize(FVector2D(640, 480))[
		SNew(SBorder).BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
			[
				SNew(SVerticalBox)

				+ SVerticalBox::Slot()
				.Padding(0)
				.VAlign(VAlign_Center)
				.AutoHeight()[
					SNew(SButton)
						.OnClicked_Static(&FTestWindowEditorModule::TestSave)
						.ContentPadding(FMargin(2.0f, 1.0f))
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						[
							SNew(STextBlock)
							.TextStyle(FEditorStyle::Get(), "NormalText.Important")
						.Font(FEditorStyle::Get().GetFontStyle("FontAwesome.10"))
						.Text(FText::FromString(FString(TEXT("Save File"))))

						]

				]

				+ SVerticalBox::Slot()
					.Padding(2)
					.AutoHeight()
					[


					SNew(SHorizontalBox)

					//Combo box for Who
					+ SHorizontalBox::Slot()
					.Padding(0)
					.VAlign(VAlign_Center)
					.FillWidth(1.0f)[
						SNew(STextComboBox)
						.OptionsSource(whoOptions)
						.OnSelectionChanged_Static(OnChangeWho)

					]

					//Combo box for Concept
					+ SHorizontalBox::Slot()
					.Padding(0)
					.VAlign(VAlign_Center)
					.FillWidth(1.0f)[
						SNew(STextComboBox)
						.OptionsSource(conceptOptions)
						.OnSelectionChanged_Static(OnChangeConcept)
					]

					//Editable wav key field
					+ SHorizontalBox::Slot()
					.Padding(0)
					.VAlign(VAlign_Center)
					.FillWidth(1.0f)
					[
						SNew(SEditableText)
						.OnTextChanged_Static(&FTestWindowEditorModule::WavTextChanged)

					]

					//Editable text field
					+SHorizontalBox::Slot()
					.Padding(0)
					.VAlign(VAlign_Center)
					.FillWidth(1.0f)
					[
						SNew(SEditableText)
						.OnTextChanged_Static(&FTestWindowEditorModule::TextChanged)

					]

					//Add Entry button
					+ SHorizontalBox::Slot()
					.Padding(0)
					.VAlign(VAlign_Center)
					.AutoWidth()
					[
						SNew(SButton)
						.OnClicked_Static(&FTestWindowEditorModule::TestClick)
						.ContentPadding(FMargin(2.0f, 1.0f))
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						[
							SNew(STextBlock)
							.TextStyle(FEditorStyle::Get(), "NormalText.Important")
							.Font(FEditorStyle::Get().GetFontStyle("FontAwesome.10"))
							.Text(FText::FromString(FString(TEXT("Add Entry"))))

						]
					]
				]

				+ SVerticalBox::Slot()[
					SAssignNew(dialogueList, SListView< TSharedPtr<DialogueEntry> >)
						.ItemHeight(24)
						
						.ListItemsSource(&dialogueEntries)
						
						.OnGenerateRow_Static(&FTestWindowEditorModule::OnGenerateWidgetForList)
						/*
						.OnContextMenuOpening(this, &STableViewTesting::GetListContextMenu)
						.SelectionMode(this, &STableViewTesting::GetSelectionMode)
						
						.HeaderRow
						(
							SNew(SHeaderRow)
							+ SHeaderRow::Column("Name")
							[
								SNew(SBorder)
								.Padding(5)
							.Content()
							[
								SNew(STextBlock)
								.Text(TEXT("Name"))
							]
							]
						+ SHeaderRow::Column("Number").DefaultLabel(TEXT("Number"))
						+ SHeaderRow::Column("TextField").DefaultLabel(TEXT("Text Field"))
						+ SHeaderRow::Column("TextBlock").DefaultLabel(TEXT("Text Block"))
						+ SHeaderRow::Column("AddChild").DefaultLabel(TEXT("Add Child"))
						)
						*/

				]

			]
	];

			//	+ SHorizontalBox::Slot().HAlign(HAlign_Center)[SNew(STextBlock).TextStyle(FEditorStyle::Get(), "Left")]

//			+ SHorizontalBox::Slot().HAlign(HAlign_Right)[SNew(STextBlock).TextStyle(FEditorStyle::Get(), "Left")]






	FSlateApplication::Get().AddWindow(window, true);
}

FReply FTestWindowEditorModule::TestClick() {
	TArray<FString> criteria;
	criteria.Init(currentString, 1);
	DialogueEntry newEntry = AddDialogueEntry(currentConcept, currentWho, currentWav, criteria);
	dialogueList.Get()->RebuildList();
	UE_LOG(TestWindowEditor, Warning, TEXT("Adding Entry: + %s"), *newEntry.ToString());

	return FReply::Handled();
}

FReply FTestWindowEditorModule::TestSave() {

	UE_LOG(TestWindowEditor, Warning, TEXT("Saving"));
	SaveEntries(FPaths::GameContentDir() + "dialogueFiles/dialogue.dat");
	return FReply::Handled();
}

void FTestWindowEditorModule::TextChanged(const FText& inText) {

	//UE_LOG(TestWindowEditor, Warning, TEXT("%s"), *inText.ToString());
	FTestWindowEditorModule::currentString = inText.ToString();
}

void FTestWindowEditorModule::WavTextChanged(const FText& inText) {

	//UE_LOG(TestWindowEditor, Warning, TEXT("%s"), *inText.ToString());
	FTestWindowEditorModule::currentWav = inText.ToString();
}

void FTestWindowEditorModule::OnChangeConcept(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo){

	currentConcept = *ItemSelected.Get();
	UE_LOG(TestWindowEditor, Warning, TEXT("Selected Concept: %s"), *currentConcept);
}


void FTestWindowEditorModule::OnChangeWho(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo) {
	currentWho = *ItemSelected.Get();
	UE_LOG(TestWindowEditor, Warning, TEXT("Selected Who: %s"), *currentWho);
}

void FTestWindowEditorModule::ShutdownModule() {
	UE_LOG(TestWindowEditor, Warning, TEXT("TestWindowEditor: Log Ended"));
}

DialogueEntry FTestWindowEditorModule::AddDialogueEntry(FString concept, FString who, FString wav, TArray<FString> criteria) {
	TSharedPtr<DialogueEntry> newEntry(new DialogueEntry(concept, who, wav, criteria));
	dialogueEntries.Add(newEntry);
	return *newEntry.Get();
}

TSharedRef<ITableRow> FTestWindowEditorModule::OnGenerateWidgetForList(TSharedPtr<DialogueEntry> InItem, const TSharedRef<STableViewBase>& OwnerTable) 
{ 
	auto table = SNew(STableRow<TSharedPtr<DialogueEntry>>, OwnerTable)[
		SNew(STextBlock).Text(FText::FromString(InItem->ToString()))

	];

		
	return table;

	

	
}



void FTestWindowEditorModule::SaveEntries(FString fileName) {
	UE_LOG(TestWindowEditor, Warning, TEXT("Saving file: %s"), *fileName);

	TArray<FString> textEntries;

	for (int i = 0; i < dialogueEntries.Num(); i++) {

		DialogueEntry de = *dialogueEntries[i].Get();

		textEntries.Add("{");
		textEntries.Add("\t" + de.who);
		textEntries.Add("\t" + de.concept);
		textEntries.Add("\t" + de.wav);

		for (int i = 0; i < de.criteria.Num(); i++) {
			textEntries.Add("\t" + de.criteria[i]);
		}


		textEntries.Add("}");
	}

	FFileHelper::SaveStringArrayToFile(textEntries, *fileName);
}


void FTestWindowEditorModule::LoadEntries(FString fileName) {
	UE_LOG(TestWindowEditor, Warning, TEXT("Loading file: %s"), *fileName);

	TArray<FString> textEntries;

	if (!FFileHelper::LoadANSITextFileToStrings(*fileName, &IFileManager::Get(), textEntries)) {
		UE_LOG(TestWindowEditor, Warning, TEXT("Unable to succesfully load file: %s"), *fileName);
		return;
	}

	dialogueEntries.Empty();


	TQueue<FString> entryQueue;

	//Add all strings to a queue and whenever we hit a } we close off the entry and add it to the entries array
	for (int i = 0; i < textEntries.Num(); i++) {



		//End of entry block
		if (textEntries[i] == "}") {

			entryQueue.Pop(); //remove the {
			FString who, concept, wav;
			TArray<FString> criteria;
			FString thisCrit;

			entryQueue.Dequeue(who);
			entryQueue.Dequeue(concept);
			entryQueue.Dequeue(wav);
			
			while (entryQueue.Dequeue(thisCrit)) {

				criteria.Add(thisCrit);

			}

			AddDialogueEntry(concept, who, wav, criteria);

		}
		else {
			entryQueue.Enqueue(textEntries[i]);
		}

	}

	

}


#undef LOCTEXT_NAMESPACE