// � 2022 CronoGames


#include "ESCharacter.h"
#include <CroAttributeComponent.h>
#include <CroActionComponent.h>

// Sets default values
AESCharacter::AESCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttributeComp = CreateDefaultSubobject<UCroAttributeComponent>(TEXT("Attribute Component"));
	ActionComp = CreateDefaultSubobject<UCroActionComponent>(TEXT("Action Component"));
}

// Called when the game starts or when spawned
void AESCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AESCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

