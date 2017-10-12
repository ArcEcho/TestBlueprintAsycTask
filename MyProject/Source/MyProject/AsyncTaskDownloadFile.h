// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Interfaces/IHttpRequest.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncTaskDownloadFile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDownloadFileUpdateProgressDelegate, int32, ReceivedDataInBytes, int32, TotalDataInBytes,const TArray<uint8>&, BinaryData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDownloadFileUnsuccssfullyDelegate);

UCLASS()
class MYPROJECT_API UAsyncTaskDownloadFile : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=( BlueprintInternalUseOnly="true" ))
	static UAsyncTaskDownloadFile* DownloadFile(FString URL);

public:
	UPROPERTY(BlueprintAssignable, Category = "AsyncTaskDownloadFile", meta = (DisplayName = "On Update Progress"))
		FDownloadFileUpdateProgressDelegate OnUpdateProgress;


	UPROPERTY(BlueprintAssignable, Category = "AsyncTaskDownloadFile", meta = (DisplayName = "On Fail"))
		FDownloadFileUnsuccssfullyDelegate OnFail;

public:

	void Start(FString URL);

private:

	/** Handles image requests coming from the web */
	void HandleFileRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	void HandleFileRequestProgress(FHttpRequestPtr HttpRequest, int32 BytesSent, int32 BytesReceived);
};
