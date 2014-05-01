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
	// Proj
	vcg->addFrame(1007.0f, 10.0f, 10.0f, 4.0f);
	// Proj Glow
	vcg->addFrame(1002.0f, 10.0f, 15.0f, 8.0f);

	// NPC Soldier
	// ----------
	// Female
	vcg->addFrame(1.0f, 922.0f, 50.0f, 50.0f);
	vcg->addFrame(51.0f, 922.0f, 50.0f, 50.0f);
	vcg->addFrame(101.0f, 922.0f, 50.0f, 50.0f);
	// Male 
	vcg->addFrame(1.0f, 973.0f, 50.0f, 50.0f);
	vcg->addFrame(51.0f, 973.0f, 50.0f, 50.0f);
	vcg->addFrame(101.0f, 973.0f, 50.0f, 50.0f);
	// Arm
	vcg->addFrame(153.0f, 1012.0f, 16.0f, 11.0f);

	// NPC health bar
	vcg->addFrame(171.0f, 1017.0f, 40.0f, 6.0f);
	// NPC health bar outline 
	vcg->addFrame(171.0f, 1011.0f, 38.0f, 4.0f);

	// NPC Smg
	vcg->addFrame(153.0f, 992.0f, 26.0f, 17.0f);
	// NPC Smg flash
	vcg->addFrame(181.0f, 1003.0f, 15.0f, 6.0f);
	// NPC Sniper
	vcg->addFrame(213.0f, 1006.0f, 41.0f, 17.0f);
	// NPC Stinger
	vcg->addFrame(256.0f, 1009.0f, 50.0f, 14.0f);

	// SCenery crate long 
	vcg->addFrame(209.0f, 1.0f,100.0f, 10.0f);

	// NPC Cow 1 
	vcg->addFrame(1.0f, 886.0f, 50.0f, 35.0f);
	// NPC Cow 2
	vcg->addFrame(52.0f, 886.0f, 50.0f, 35.0f);

	// Missile
	vcg->addFrame(980.0f, 1.0f, 20.0f, 11.0f);
	// Basic Expl 1 
	vcg->addFrame(1.0f, 103.0f, 60.0f, 60.0f);
	// Basic Expl 2
	vcg->addFrame(63.0f, 103.0f, 60.0f, 60.0f);
	// Basic Expl 3 
	vcg->addFrame(125.0f, 103.0f, 60.0f, 60.0f);
	// Basic Expl 4 
	vcg->addFrame(187.0f, 103.0f, 60.0f, 60.0f);

	// Particle sphere
	vcg->addFrame(1.0f, 166.0f, 30.0f, 30.0f);
	// Particle smoke 1
	vcg->addFrame(33.0f, 165.0f, 20.0f, 20.0f);
	// Particle smoke 2
	vcg->addFrame(55.0f, 165.0f, 20.0f, 20.0f);
	// Particle smoke 3
	vcg->addFrame(77.0f, 165.0f, 20.0f, 20.0f);
	// Particle smoke 4
	vcg->addFrame(99.0f, 165.0f, 20.0f, 20.0f);
	// Particle smoke 5
	vcg->addFrame(121.0f, 165.0f, 20.0f, 20.0f);

	// NPC Heavy Soldier
	vcg->addFrame(1.0f, 834.0f, 50.0f, 50.0f);
	vcg->addFrame(51.0f, 834.0f, 50.0f, 50.0f);
	vcg->addFrame(101.0f, 834.0f, 50.0f, 50.0f);
	// NPC Heavy Soldier Arm
	vcg->addFrame(153.0f, 979.0f, 16.0f, 11.0f);

	// NPC Tank 
	vcg->addFrame(1.0f, 782.0f, 124.0f, 50.0f);
	// NPC Tank Barrel
	vcg->addFrame(181.0f, 994.0f, 65.0f, 7.0f);

	// Grab the arrays 
	verts = vcg->getVertices();
	cords = vcg->getCoords();
	delete(vcg);
}