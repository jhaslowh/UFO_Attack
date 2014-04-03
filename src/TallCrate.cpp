#include "TallCrate.h"


TallCrate::TallCrate() : SceneryObject()
{
	type = "tallCrate";
	width = 10.0f;
	height = 100.0f;
	originX = 50.0f;
	originY = 5.0f;
	rotation = 90.0f;
	imageID = GI_CRATE_LONG;
	collides = true;
	stopsPlayer = true;
	collisionRec = new Rec();
	fixCollRec();
	next = NULL;
}

TallCrate::~TallCrate(){}

// Fix collision rec location 
void TallCrate::fixCollRec(){
	if (collisionRec){
		collisionRec->setLocation(locX - originY, locY - originX);
		collisionRec->setSize(width, height);
	}
}