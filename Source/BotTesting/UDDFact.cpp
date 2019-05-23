// Fill out your copyright notice in the Description page of Project Settings.

#include "UDDFact.h"



UDDFact::UDDFact() {

	return;
}
UDDFact::UDDFact(FName key, FName value)
{
	key = key;
	value = value;
	return;
}

UDDFact::~UDDFact()
{
	return;
}


bool UDDFact::Compare(UDDFact* f2) {

	//FString str = FString::Printf(TEXT("Comparing %llu , %llu  to   %llu , %llu"), &key, &value, &f2->key, &f2->value);
	if (f2 == nullptr) {
		return false;
	}

	if (!key.IsEqual(f2->GetKey()) || !value.IsEqual(f2->GetValue()) )
	{
		//UE_LOG(LogTemp, Warning, TEXT("[FAIL] Comparing { %s, %s }, to { %s, %s }"), *key.ToString(), *value.ToString(), *f2->GetKey().ToString(), *f2->GetValue().ToString())
		return false;
	}
	//UE_LOG(LogTemp, Warning, TEXT("[PASS] Comparing { %s, %s }, to { %s, %s }"), *key.ToString(), *value.ToString(), *f2->GetKey().ToString(), *f2->GetValue().ToString())
	return true;
}

bool UDDFact::Initialize(FName fkey, FName fvalue) {
	//FString str = FString::Printf(TEXT("Converted %s , %s to   %llu , %llu"), *fkey, *fvalue, (int64*)(TCHAR_TO_UTF8(*fkey)), (int64*)(TCHAR_TO_UTF8(*fvalue)));
	//FString str = FString::Printf(TEXT("Converted %s , %s to   %llu , %llu"), fkey, fvalue, (int64*)(TCHAR_TO_UTF8(*fkey)), (int64*)(TCHAR_TO_UTF8(*fvalue)));

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
	//key = (int64*)(TCHAR_TO_UTF8(*fkey));
	//value = (int64*)(TCHAR_TO_UTF8(*fvalue));
	key = fkey;
	value = fvalue;

	return true;
}
