// © 2022 CronoGames


#include "ESInventorySlotWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"

bool UESInventorySlotWidget::Initialize()
{
	const bool bSuccess = Super::Initialize();
	if (!bSuccess) { return false; }

	if (ensure(SlotButton != nullptr)) { return false; }
	if (ensure(SlotImage != nullptr)) { return false; }
	SlotButton->OnClicked.AddDynamic(this, &UESInventorySlotWidget::OnSlotClicked);
	SlotButton->OnHovered.AddDynamic(this, &UESInventorySlotWidget::OnSlotHovered);
	SlotButton->OnUnhovered.AddDynamic(this, &UESInventorySlotWidget::OnSlotUnHovered);
	return bSuccess;
}

void UESInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetDefaultStyle();
	SlotImage->SetBrushSize(FVector2D(128.0f, 128.0f));
}

void UESInventorySlotWidget::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnAddedToFocusPath(InFocusEvent);
	SetActiveStyle();
}

void UESInventorySlotWidget::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnRemovedFromFocusPath(InFocusEvent);
	if (!SlotImage->Brush.GetResourceObject())
	{
		SetDefaultStyle();
	}
}

void UESInventorySlotWidget::OnSlotClicked()
{
	SetActiveStyle();
	UE_LOG(LogTemp, Log, TEXT("Slot %d was clicked"), SlotIndex);
}

void UESInventorySlotWidget::OnSlotHovered()
{
	if (SlotImage->Brush.GetResourceObject())
	{
		OnHovered.Broadcast(SlotType, SlotIndex);
	}
}

void UESInventorySlotWidget::OnSlotUnHovered()
{
	OnUnHovered.Broadcast();
}

void UESInventorySlotWidget::SetImageVisibility()
{
	if (SlotImage->Brush.GetResourceObject())
	{
		SlotImage->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SlotImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UESInventorySlotWidget::SetDefaultStyle()
{
	FSlateBrush Normal;
	Normal.DrawAs = ESlateBrushDrawType::Image;
	Normal.Tiling = ESlateBrushTileType::NoTile;
	Normal.Mirroring = ESlateBrushMirrorType::NoMirror;
	Normal.TintColor = FSlateColor(FLinearColor(0.442708f, 0.442708f, 0.442708f, 0.561905f));

	FSlateBrush Hovered;
	Hovered.DrawAs = ESlateBrushDrawType::Image;
	Hovered.Tiling = ESlateBrushTileType::NoTile;
	Hovered.Mirroring = ESlateBrushMirrorType::NoMirror;
	Hovered.TintColor = FSlateColor(FLinearColor(1.0f, 0.366253f, 0.015209f, 1.0f));

	FSlateBrush Pressed;
	Pressed.DrawAs = ESlateBrushDrawType::Image;
	Pressed.Tiling = ESlateBrushTileType::NoTile;
	Pressed.Mirroring = ESlateBrushMirrorType::NoMirror;
	Pressed.TintColor = FSlateColor(FLinearColor(0.619792f, 0.22701f, 0.009426f, 1.0f));

	FButtonStyle DefaultStyle;
	DefaultStyle.Normal = Normal;
	DefaultStyle.Hovered = Hovered;
	DefaultStyle.Pressed = Pressed;

	if (SlotImage->Brush.GetResourceObject())
	{
		SetImageVisibility();
		SlotButton->SetStyle(DefaultStyle);
	}
}

void UESInventorySlotWidget::SetActiveStyle()
{
	FSlateBrush Normal;
	Normal.DrawAs = ESlateBrushDrawType::Image;
	Normal.Tiling = ESlateBrushTileType::NoTile;
	Normal.Mirroring = ESlateBrushMirrorType::NoMirror;
	Normal.TintColor = FSlateColor(FLinearColor(1.0f, 0.33253f, 0.015209f, 1.0f));

	FSlateBrush Hovered;
	Hovered.DrawAs = ESlateBrushDrawType::Image;
	Hovered.Tiling = ESlateBrushTileType::NoTile;
	Hovered.Mirroring = ESlateBrushMirrorType::NoMirror;
	Hovered.TintColor = FSlateColor(FLinearColor(1.0f, 0.442751f, 0.0f, 1.0f));

	FSlateBrush Pressed;
	Pressed.DrawAs = ESlateBrushDrawType::Image;
	Pressed.Tiling = ESlateBrushTileType::NoTile;
	Pressed.Mirroring = ESlateBrushMirrorType::NoMirror;
	Pressed.TintColor = FSlateColor(FLinearColor(0.619792f, 0.22701f, 0.009426f, 1.0f));

	FButtonStyle DefaultStyle;
	DefaultStyle.Normal = Normal;
	DefaultStyle.Hovered = Hovered;
	DefaultStyle.Pressed = Pressed;

	if (SlotImage->Brush.GetResourceObject())
	{
		SetImageVisibility();
		SlotButton->SetStyle(DefaultStyle);
	}
}

void UESInventorySlotWidget::SetSlotType(EInventorySlotType Type)
{
	SlotType = Type;
}
