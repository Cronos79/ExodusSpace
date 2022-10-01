// © 2022 CronoGames

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "ESHTTPBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class EXODUSSPACE_API UESHTTPBase : public UObject
{
	GENERATED_BODY()

protected:
	FHttpModule* ESHttp;

public:
	UPROPERTY( EditAnywhere ,BlueprintReadWrite, Category = "HTTP")
	FString Url{"Enter url"};
	UPROPERTY( EditAnywhere ,BlueprintReadWrite, Category = "HTTP")
	FString ESUser{"Enter Login name"};

public:
	UESHTTPBase();

	UFUNCTION()
	void SendHTTPGet(FString UserName);

	UFUNCTION()
	void OnGetLoginResponse();
};
