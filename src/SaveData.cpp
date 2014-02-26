#include "SaveData.h"


SaveData::SaveData()
{
	purchasedItems = new bool[StoreItems::STORE_ITEM_COUNT];
	humanAbductCount = 0;
	animalAbductCount = 0;
}

SaveData::~SaveData()
{
	delete purchasedItems;
}

// Set the specificed item as purchased 
void SaveData::itemPurchsed(int index){
	purchasedItems[index] = true;
}
// Get the state of an item 
bool SaveData::isItemPurchased(int index){
	return purchasedItems[index];
}

// Set human abduct count 
void SaveData::setHumanAbductCount(int value){humanAbductCount = value;}
// Get human abduct count 
int SaveData::getHumanAbductCount(){return humanAbductCount;}
	
// Set Animal abduct count 
void SaveData::setAnimalAbductCount(int value){animalAbductCount = value;}
// Get Animal abduct count 
int SaveData::getAnimalAbductCount(){return animalAbductCount;}
	

// Change the abduction count of animals by the sent amout
void SaveData::incrAnimalCount(int value){animalAbductCount += value;}

// Change the abduction count of humans by the sent amout
void SaveData::incrHumanCount(int value){humanAbductCount += value;}