#include "StoreItem.h"


StoreItem::StoreItem(int i, std::string n, std::string d, int ap, int hp, std::string file){
	index = i;
	name = n;
	desc = d;
	animalPrice = ap;
	humanPrice = hp;
	image = file;
}

int StoreItem::getIndex(){return index;}
std::string StoreItem::getName(){return name;}
std::string StoreItem::getDesc(){return desc;}
int StoreItem::getAnimalPrice(){return animalPrice;}
int StoreItem::getHumanPrice(){return humanPrice;}
std::string StoreItem::getImage(){return image;}