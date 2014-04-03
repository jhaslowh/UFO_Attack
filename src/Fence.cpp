#include "Fence.h"


Fence::Fence(): SceneryObject()
{
	type = "fence";
	width = 25.0f;
	height = 25.0f;
	imageID = GI_FENCE;
	collides = true;
	stopsPlayer = true;
	collisionRec = new Rec(0.0f,0.0f,width, height);
	next = NULL;
}

Fence::~Fence()
{

}
