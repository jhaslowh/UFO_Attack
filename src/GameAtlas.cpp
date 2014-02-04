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

	// Grab the arrays 
	verts = vcg->getVertices();
	cords = vcg->getCoords();
	delete(vcg);
}