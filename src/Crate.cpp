#include "Crate.h"

Crate::Crate() : SceneryObject()
{
	type = "crate";
	width = 25.0f;
	height = 25.0f;
	imageID = GI_CRATE;
	collides = true;
	stopsPlayer = true;
	collisionRec = new Rec(0.0f,0.0f,width, height);
	next = NULL;
}

Crate::~Crate(){}
