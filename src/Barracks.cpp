#include "Barracks.h"

Barracks::Barracks()
{	
	type = "barracks";
	width = 100.0f;
	height = 57.0f;
	originX = 0.0f;
	originY = 0.0f;
	collides = false;
	stopsPlayer = false;
	imageID = GI_BARRACKS;
}

Barracks::~Barracks()
{

}
