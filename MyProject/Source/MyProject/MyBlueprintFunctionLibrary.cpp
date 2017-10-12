// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBlueprintFunctionLibrary.h"
#include "Internationalization.h"
#include "UnrealMemory.h"



void UMyBlueprintFunctionLibrary::ChangeLocalization(FString target)
{
	FInternationalization::Get().SetCurrentCulture(target);
}

FString UMyBlueprintFunctionLibrary::StringFromBinaryArray(const TArray<uint8>& BinaryArray)
{
	TArray<uint8> BinaryArrayCopy;
	BinaryArrayCopy.AddUninitialized(BinaryArray.Num());
	FMemory::Memcpy(BinaryArrayCopy.GetData(), BinaryArray.GetData(), BinaryArrayCopy.Num());
	BinaryArrayCopy.Add(0);

	return FString(ANSI_TO_TCHAR(reinterpret_cast<const char*>(BinaryArrayCopy.GetData())));
}
