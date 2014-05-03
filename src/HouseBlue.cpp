#include "HouseBlue.h"


HouseBlue::HouseBlue()
{
	type = "houseBlue";
	width = 150.0f;
	height = 200.0f;
	originX = 0.0f;
	originY = 0.0f;
	collides = false;
	stopsPlayer = false;
	imageID = GI_HOUSE_BLUE;
}


HouseBlue::~HouseBlue()
{
}
