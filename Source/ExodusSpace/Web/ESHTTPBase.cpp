// © 2022 CronoGames


#include "ESHTTPBase.h"

UESHTTPBase::UESHTTPBase()
{
	ESHttp = &FHttpModule::Get();
}

void UESHTTPBase::SendHTTPGet(FString UserName)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = ESHttp->CreateRequest();

	//Request->OnProcessRequestComplete().BindUObject(this, &ThisClass::OnGetLoginResponse);
	Request->SetURL(FString::Printf(TEXT("%s?%s"), *Url, *UserName));
}

void UESHTTPBase::OnGetLoginResponse()
{

}
