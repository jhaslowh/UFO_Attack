#include "GameAtlas.h"

GameAtlas::GameAtlas() : TextureAtlas(){}
GameAtlas::~GameAtlas(){}

// Set up the stucture of this atlas 
void GameAtlas::init(){
	// Load texture
	textureID = loadPNG(std::string("images/gameSheet.png"));

	VertCordGenerator* vcg = new VertCordGenerator(1024,1024);

	// Add Game elements to the buffers
	// Tree
	vcg->addFrame(1.0f,1.0f,100.0f,100.0f);
	// UFO
	vcg->addFrame(1.0f,103.0f,100.0f,50.0f);

	// Grab the arrays 
	verts = vcg->getVertices();
	cords = vcg->getCoords();
	delete(vcg);
}