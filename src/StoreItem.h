#pragma once
#include <string>

class StoreItem
{
	int index;			// Index of this in exterior array
	std::string name;	// Name 
	std::string desc;	// Description 
	int animalPrice;	// Animal price
	int humanPrice;		// Human price 
	std::string image;	// image file

public:
	StoreItem(int i, std::string n, std::string d, int ap, int hp, std::string file);

	int getIndex();
	std::string getName();
	std::string getDesc();
	int getAnimalPrice();
	int getHumanPrice();
	std::string getImage();
};

