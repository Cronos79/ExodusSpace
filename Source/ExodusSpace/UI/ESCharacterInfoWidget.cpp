// © 2022 CronoGames


#include "ESCharacterInfoWidget.h"
#include "CroItem.h"
#include "ESInventorySlotWidget.h"

bool UESCharacterInfoWidget::Initialize()
{
	const bool bSuccess = Super::Initialize();
	if (!bSuccess) { return false; }

	if (ensure(HeadSlot != nullptr)) { return false; }
	HeadSlot->SlotType = EInventorySlotType::Helm;
	if (ensure(ShoulderSlot != nullptr)) { return false; }
	ShoulderSlot->SlotType = EInventorySlotType::Shoulder;
	if (ensure(ChestSlot != nullptr)) { return false; }
	ChestSlot->SlotType = EInventorySlotType::Chest;
	if (ensure(GlovesSlot != nullptr)) { return false; }
	GlovesSlot->SlotType = EInventorySlotType::Gloves;
	if (ensure(BracersSlot != nullptr)) { return false; }
	BracersSlot->SlotType = EInventorySlotType::Bracers;
	if (ensure(BeltSlot != nullptr)) { return false; }
	BeltSlot->SlotType = EInventorySlotType::Belt;
	if (ensure(LegsSlot != nullptr)) { return false; }
	LegsSlot->SlotType = EInventorySlotType::Legs;
	if (ensure(BootsSlot != nullptr)) { return false; }
	BootsSlot->SlotType = EInventorySlotType::Boots;
	if (ensure(NeckSlot != nullptr)) { return false; }
	NeckSlot->SlotType = EInventorySlotType::Neck;
	if (ensure(LeftRingSlot != nullptr)) { return false; }
	LeftRingSlot->SlotType = EInventorySlotType::LeftRing;
	if (ensure(RightRingSlot != nullptr)) { return false; }
	RightRingSlot->SlotType = EInventorySlotType::RightRing;
	if (ensure(MainHandSlot != nullptr)) { return false; }
	MainHandSlot->SlotType = EInventorySlotType::MainHand;
	if (ensure(OffHandSlot != nullptr)) { return false; }
	OffHandSlot->SlotType = EInventorySlotType::OffHand;

	return bSuccess;
}
