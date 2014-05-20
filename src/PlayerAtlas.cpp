#include "PlayerAtlas.h"


PlayerAtlas::PlayerAtlas(){}

PlayerAtlas::~PlayerAtlas(){}

// Set up the stucture of this atlas 
void PlayerAtlas::load(){
	// Load texture
	textureID = loadPNG( std::string("images/AtlasPlayer.png"));
	VertCordGenerator* vcg = new VertCordGenerator(512,512);

	// Add Player images to the buffers
	// Player Run frames 
	vcg->addFrame(1,1,50,50);
	vcg->addFrame(53,1,50,50);
	vcg->addFrame(105,1,50,50);
	vcg->addFrame(157,1,50,50);

	vcg->addFrame(1,53,50,50);
	vcg->addFrame(53,53,50,50);
	vcg->addFrame(105,53,50,50);
	vcg->addFrame(157,53,50,50);

	vcg->addFrame(1,105,50,50);
	vcg->addFrame(53,105,50,50);
	vcg->addFrame(105,105,50,50);
	vcg->addFrame(157,105,50,50);

	// UFO
	vcg->addFrame(209.0f,1.0f,100.0f,50.0f);
	// UFO Bear
	vcg->addFrame(209.0f,52.0f, 100.0f, 50.0f);
	// Health bar
	vcg->addFrame(311.0f,1.0f,100.0f,10.0f);
	// Player arm
	vcg->addFrame(208.0f, 104.0f, 50.0f,50.0f);
	// Player Laser Gun
	vcg->addFrame(311.0f, 13.0f, 21.0f, 17.0f);
	// Player Laser Gun Muz
	vcg->addFrame(334.0f, 13.0f, 12.0f, 12.0f);
	// Player Shotgun 
	vcg->addFrame(311.0f, 32.0f, 34.0f, 17.0f);
	// Player Shotgun flash 
	vcg->addFrame(348.0f, 13.0f, 18.0f, 12.0f);
	// Player SMG
	vcg->addFrame(311.0f, 51.0f, 32.0f, 23.0f);

	// UFO Ray
	vcg->addFrame(1.0f, 474.0f,248.0f,37.0f);

	// UFO Rocket
	vcg->addFrame(347.0f, 27.0f, 43.0f, 17.0f);
	// UFO Machine Gun
	vcg->addFrame(347.0f, 46.0f, 42.0f, 11.0f);
	// UFO Cowtapult 
	vcg->addFrame(347.0f, 59.0f, 90.0f, 32.0f);

	// Grab the arrays 
	verts = vcg->getVertices();
	cords = vcg->getCoords();
	delete vcg;
}