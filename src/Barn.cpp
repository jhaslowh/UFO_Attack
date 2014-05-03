#include "Barn.h"


Barn::Barn()
{
	type = "barn";
	width = 240.0f;
	height = 150.0f;
	originX = 0.0f;
	originY = 0.0f;
	collides = false;
	stopsPlayer = false;
	imageID = GI_BARN;
}

Barn::~Barn()
{

}
