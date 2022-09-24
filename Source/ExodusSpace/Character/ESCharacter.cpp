// © 2022 CronoGames


#include "ESCharacter.h"
#include <CroAttributeComponent.h>
#include <CroActionComponent.h>
#include "Components/WidgetComponent.h"
#include "../UI/SimpleHealthBar.h"
#include "Kismet/GameplayStatics.h"
#include "../UI/SimpleCombatText.h"

// Sets default values
AESCharacter::AESCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CombatText = CreateDefaultSubobject<UWidgetComponent>(TEXT("CombatText"));
	CombatText->SetupAttachment(GetMesh());
	CombatText->SetWidgetSpace(EWidgetSpace::Screen);
	CombatText->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));
	CombatText->SetWidgetClass(CombatTextClass);

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar"));
	HealthBar->SetupAttachment(GetMesh());
	HealthBar->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBar->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));
	HealthBar->SetWidgetClass(HealthbarClass);

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
}

// Called every frame
void AESCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AESCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	AController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (NewController == PC && HealthBar)
	{
		HealthBar->SetVisibility(false, true);
		//CombatText->SetVisibility(false, true);
	}
}

void AESCharacter::OnHealthChange(AActor* InstigatorActor, UCroAttributeComponent* OwningComp, float NewHealth, float MaxHealth, float ChangedAmount)
{
	UpdateHealthBar(NewHealth, MaxHealth);

	USimpleCombatText* CT = Cast<USimpleCombatText>(CombatText->GetWidget());
	if (CT)
	{
		CT->PlayCombatText(ChangedAmount);
	}
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

void AESCharacter::GainCredits(int32 Value)
{
	Credits += Value;
	OnCreditsChanged.Broadcast(Value);
}

bool AESCharacter::SpendCredits(int32 Value)
{
	if (Credits >= Value)
	{
		Credits -= Value;
		OnCreditsChanged.Broadcast(Value);
		return true;
	}
	return false;
}

bool AESCharacter::HasEnoughMana_Implementation(float Amount)
{
	if (AttributeComp)
	{
		return AttributeComp->HasEnoughMana(Amount);
	}
	return false;
}

float AESCharacter::GetCurrentMana_Implementation()
{
	if (AttributeComp)
	{
		return AttributeComp->GetMana();
	}
	return 0;
}

bool AESCharacter::UseMana_Implementation(float Amount)
{
	if (AttributeComp)
	{
		return AttributeComp->UseMana(Amount);
	}
	return false;
}

