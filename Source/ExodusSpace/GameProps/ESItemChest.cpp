// © 2022 CronoGames


#include "ESItemChest.h"
#include <Components/StaticMeshComponent.h>

// Sets default values
AESItemChest::AESItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base mesh"));
	RootComponent = BaseMesh;
	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lid mesh"));
	LidMesh->SetupAttachment(BaseMesh);
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

void AESItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, TargetRoll));
}

