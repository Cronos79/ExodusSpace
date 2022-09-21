// © 2022 CronoGames


#include "ESCharacter.h"
#include <CroAttributeComponent.h>
#include <CroActionComponent.h>
#include "Components/WidgetComponent.h"
#include "../UI/SimpleHealthBar.h"

// Sets default values
AESCharacter::AESCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar"));
	HealthBar->SetupAttachment(GetMesh());
	HealthBar->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBar->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));
	HealthBar->SetWidgetClass(USimpleHealthBar::StaticClass());

	AttributeComp = CreateDefaultSubobject<UCroAttributeComponent>(TEXT("Attribute Component"));
	ActionComp = CreateDefaultSubobject<UCroActionComponent>(TEXT("Action Component"));
}

// Called when the game starts or when spawned
void AESCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (AttributeComp)
	{
		AttributeComp->OnHealthChanged.AddDynamic(this, &AESCharacter::OnHealthChange);
	}	
	USimpleHealthBar* HealthBarUI = Cast<USimpleHealthBar>(HealthBar->GetWidget());
	if (HealthBarUI)
	{
		HealthBarUI->BarPawn = this;
	}
}

// Called every frame
void AESCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AESCharacter::OnHealthChange(AActor* InstigatorActor, UCroAttributeComponent* OwningComp, float NewHealth, float MaxHealth, float ChangedAmount)
{
	UpdateHealthBar(NewHealth, MaxHealth);
}

void AESCharacter::UpdateHealthBar(float CurrentValue, float MaxValue)
{
	USimpleHealthBar* HealthBarUI = Cast<USimpleHealthBar>(HealthBar->GetWidget());
	if (HealthBarUI->HealthBar)
	{
		const float Percent = CurrentValue / MaxValue;
		HealthBarUI->HealthBar->SetPercent(Percent);
	}
}

