#include "NPC.h"


NPC::NPC()
{	
	locX = 0.0f;
	locY = 0.0f;
	width = 0.0f;
	height = 0.0f;
	originX = 0.0f;
	originY = 0.0f;
	rotation = 0.0f;
	scale = 1.0f;
	imageID = 0;
	collisionRec = new Rec();
	next = NULL;
}

NPC::~NPC()
{
	delete collisionRec;
	delete next;
}

// Set the location of the npc 
void NPC::setLocation(float x, float y){
	locX = x;
	locY = y;
	fixCollRec();
}
float NPC::getX(){return locX;}
float NPC::getY(){return locY;}
// Set the width and height of the npc
void NPC::setSize(float w, float h){
	width = w;
	height = h;
}
float NPC::getWidth(){return width;}
float NPC::getHeight(){return height;}
// Set the origin point of the npc
void NPC::setOrigin(float x, float y){
	originX = x;
	originY = y;
}
// Set the rotation of the npc
void NPC::setRotation(float r){
	rotation = r;
}
float NPC::getRotation(){return rotation;}
// Set the scale of the npc
void NPC::setScale(float s){
	scale = s;
}
float NPC::getScale(){return scale;}
// Set the image id to draw for this npc
void NPC::setImageID(int id){
	imageID = id;
}
int NPC::getImageID(){return imageID;}

// Returns npc collision rec
Rec* NPC::getCollisionRec(){return collisionRec;}

// Fix collision rec location 
void NPC::fixCollRec(){
	if (collisionRec){
		collisionRec->setLocation(locX - originX, locY - originY);
		collisionRec->setSize(width, height);
	}
}

// Update game state of the npc object
void NPC::update(float deltaTime, Handlers* handlers){
	// Nothing to do 
}

// Draw any light this object has 
void NPC::drawLight(GLHandler* mgl, GameAtlas* mGame){
	// Nothing to do
}

// Draw object to the screen
void NPC::draw(GLHandler* mgl, GameAtlas* mGame){
	mGame->draw(mgl,imageID, locX, locY, scale, rotation, originX, originY);
}

