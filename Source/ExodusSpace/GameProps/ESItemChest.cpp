// © 2022 CronoGames


#include "ESItemChest.h"
#include <Components/StaticMeshComponent.h>
#include <Net/UnrealNetwork.h>

// Sets default values
AESItemChest::AESItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base mesh"));
	RootComponent = BaseMesh;
	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lid mesh"));
	LidMesh->SetupAttachment(BaseMesh);

	SetReplicates(true);
}

// Called when the game starts or when spawned
void AESItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AESItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AESItemChest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AESItemChest, bLidOpened);
}

void AESItemChest::OnRep_LidOpened()
{
	float CurrRoll = bLidOpened ? TargetRoll : 0.0f;
	LidMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, CurrRoll));
}

void AESItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	bLidOpened = !bLidOpened;
	OnRep_LidOpened();
}

