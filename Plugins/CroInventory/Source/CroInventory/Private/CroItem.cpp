// © 2022 CronoGames


#include "CroItem.h"

void UCroItem::InitItem(EInventorySlotType NewItemType, FName NewItemName, FString NewItemDesc)
{
	ItemType = NewItemType;
	ItemName = NewItemName;
	ItemDesc = NewItemDesc;
}
