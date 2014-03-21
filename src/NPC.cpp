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
	next = NULL;
	
	canBeObducted = true;
	beingAbducted = false;
	alive = true;
	health = 100.0f;
}

NPC::~NPC()
{
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
Rec* NPC::getCollisionRec(){return &collisionRec;}

// Fix collision rec location 
void NPC::fixCollRec(){
	collisionRec.setLocation(locX - originX + bounds.getX(), locY - originY + bounds.getX());
	collisionRec.setSize(bounds.getWidth(), bounds.getHeight());
}

// Update movement of the NPC 
// This method should set the movement values for the npc.
void NPC::updateMovement(float deltaTime, Handlers* handlers){
	// Nothing to do
}

// Update collision of NPC 
// This method should check if the npc is being abducted, if it is
// it should ignore the movement from the update movement method and 
// if it isnt, it should resolve the movement and collisions. 
void NPC::updateCollision(float deltaTime, Handlers* handlers){
	// TODO check if being abducted

	beingAbducted = false;
}

// Update game state of the npc object
// Do any non movement or collision detection updates
// (weapons and the like) 
void NPC::update(float deltaTime, Handlers* handlers){
	// Nothing to do
}

// Draw any light this object has 
void NPC::drawLight(GLHandler* mgl, GameAtlas* mGame){
	// Nothing to do
}

// Draw object to the screen
void NPC::draw(GLHandler* mgl, GameAtlas* mGame){
	// Nothing to do
}
