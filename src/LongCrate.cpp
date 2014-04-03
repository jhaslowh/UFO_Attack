#include "LongCrate.h"

LongCrate::LongCrate() : SceneryObject()
{
	type = "longCrate";
	width = 100.0f;
	height = 10.0f;
	originX = 50.0f;
	originY = 5.0f;
	imageID = GI_CRATE_LONG;
	collides = true;
	stopsPlayer = true;
	collisionRec = new Rec(0.0f,0.0f,width, height);
	next = NULL;
}

LongCrate::~LongCrate(){}