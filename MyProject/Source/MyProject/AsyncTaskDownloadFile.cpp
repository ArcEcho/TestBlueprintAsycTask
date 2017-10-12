// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AsyncTaskDownloadFile.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"


//----------------------------------------------------------------------//
// UAsyncTaskDownloadFile
//----------------------------------------------------------------------//

UAsyncTaskDownloadFile::UAsyncTaskDownloadFile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		AddToRoot();
	}
}

UAsyncTaskDownloadFile* UAsyncTaskDownloadFile::DownloadFile(FString URL)
{
	UAsyncTaskDownloadFile* DownloadTask = NewObject<UAsyncTaskDownloadFile>();
	DownloadTask->Start(URL);

	return DownloadTask;
}

void UAsyncTaskDownloadFile::Start(FString URL)
{
#if !UE_SERVER
	// Create the Http request and add to pending request list
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UAsyncTaskDownloadFile::HandleFileRequest);
	HttpRequest->OnRequestProgress().BindUObject(this, &UAsyncTaskDownloadFile::HandleFileRequestProgress);
	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb(TEXT("GET"));
	HttpRequest->ProcessRequest();
#else
	// On the server we don't execute fail or success we just don't fire the request.
	RemoveFromRoot();
#endif
}

void UAsyncTaskDownloadFile::HandleFileRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
#if !UE_SERVER
	RemoveFromRoot();

	if (bSucceeded && HttpResponse.IsValid() && HttpResponse->GetContentLength() > 0)
	{
		OnUpdateProgress.Broadcast(HttpResponse->GetContentLength(), HttpResponse->GetContentLength(), HttpResponse->GetContent());
		return;
	}

	OnFail.Broadcast();

#endif
}

void UAsyncTaskDownloadFile::HandleFileRequestProgress(FHttpRequestPtr HttpRequest, int32 BytesSent, int32 BytesReceived)
{
#if !UE_SERVER
	if (HttpRequest->GetResponse()->GetContentLength() > 0)
	{
		TArray<uint8> EmptyData;
		OnUpdateProgress.Broadcast(BytesReceived, HttpRequest->GetResponse()->GetContentLength(), EmptyData);
	}
#endif
}
