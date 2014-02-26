#pragma once
#include "StoreItems.h"

class SaveData
{
	// Bool of all purchased items 
	bool* purchasedItems;
	// Number of abducted humans 
	int humanAbductCount;
	// Number of abducted animals
	int animalAbductCount;

public:
	SaveData();
	~SaveData();

	// Set the specificed item as purchased 
	void itemPurchsed(int index);
	// Get the state of an item 
	bool isItemPurchased(int index);

	// Set human abduct count 
	void setHumanAbductCount(int value);
	// Get human abduct count 
	int getHumanAbductCount();
	
	// Set Animal abduct count 
	void setAnimalAbductCount(int value);
	// Get Animal abduct count 
	int getAnimalAbductCount();
	

	// Change the abduction count of animals by the sent amout
	void incrAnimalCount(int value);

	// Change the abduction count of humans by the sent amout
	void incrHumanCount(int value);
};

