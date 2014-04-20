#include "ProjTemplate.h"

ProjTemplate::ProjTemplate()
{
	speed = 1000.0f;
	imageId = -1;
	imageOrigin[0] = 0.0f;
	imageOrigin[1] = 0.0f;
	glowImageId = -1;
	glowImageOrigin[0] = 0.0f; 
	glowImageOrigin[1] = 0.0f; 
	explodes = false;
	drawColor[0] = 1.0f;
	drawColor[1] = 1.0f;
	drawColor[2] = 1.0f;
	drawColor[3] = 1.0f;
}

// Set the color for the template
void ProjTemplate::setColor(float r, float g, float b, float a){
	drawColor[0] = r;
	drawColor[1] = g;
	drawColor[2] = b;
	drawColor[3] = a;
}
