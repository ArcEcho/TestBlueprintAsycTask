// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 *
 */
UCLASS()
class MYPROJECT_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Change Localization"), Category = "Locale")
		static void ChangeLocalization(FString target);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "String From Binary Array"))
	static FString StringFromBinaryArray(const TArray<uint8>& BinaryArray);
};