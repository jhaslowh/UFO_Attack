#include "GameAtlas.h"

GameAtlas::GameAtlas() : TextureAtlas(){}
GameAtlas::~GameAtlas(){}

// Set up the stucture of this atlas 
void GameAtlas::load(){
	// Load texture
	textureID = loadPNG(std::string("images/AtlasGame.png"));

	VertCordGenerator* vcg = new VertCordGenerator(1024,1024);

	// Add Game elements to the buffers
	// Tree
	vcg->addFrame(1.0f,1.0f,100.0f,100.0f);
	// Sign
	vcg->addFrame(103.0f,1.0f,50.0f,50.0f);
	// Hay Bale
	vcg->addFrame(103.0f,53.0f,25.0f,25.0f);
	// Crate 
	vcg->addFrame(155.0f,1.0f,25.0f,25.0f);
	// Fence
	vcg->addFrame(181.0f,1.0f,25.0f,25.0f);
	// Sky 
	vcg->addFrame(1022.0f, 1.0f, 1.0f, 1022.0f);
	// Sky Glow 
	vcg->addFrame(1019.0f, 1.0f, 1.0f, 1022.0f);

	// Grab the arrays 
	verts = vcg->getVertices();
	cords = vcg->getCoords();
	delete(vcg);
}