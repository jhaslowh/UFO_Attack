#include "PlayerAtlas.h"


PlayerAtlas::PlayerAtlas(){}

PlayerAtlas::~PlayerAtlas(){}

// Set up the stucture of this atlas 
void PlayerAtlas::load(){
	// Load texture
	textureID = loadPNG( std::string("images/playerAtlas.png"));
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

	// Grab the arrays 
	verts = vcg->getVertices();
	cords = vcg->getCoords();
	delete(vcg);
}