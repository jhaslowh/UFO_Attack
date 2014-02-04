#include "SceneryObject.h"


SceneryObject::SceneryObject()
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
	collides = false;
	collisionRec = new Rec();
	next = NULL;
}

SceneryObject::~SceneryObject()
{
	delete collisionRec;
}

// Getters and setters 

// Set the location of the scenerey 
void SceneryObject::setLocation(float x, float y){
	locX = x;
	locY = y;
	fixCollRec();
}
float SceneryObject::getX(){return locX;}
float SceneryObject::getY(){return locY;}
// Set the width and height of the scenery
void SceneryObject::setSize(float w, float h){
	width = w;
	height = h;
}
float SceneryObject::getWidth(){return width;}
float SceneryObject::getHeight(){return height;}
// Set the origin point of the scenery
void SceneryObject::setOrigin(float x, float y){
	originX = x;
	originY = y;
}
// Set the rotation of the scenery
void SceneryObject::setRotation(float r){
	rotation = r;
}
float SceneryObject::getRotation(){return rotation;}
// Set the scale of the scenery
void SceneryObject::setScale(float s){
	scale = s;
}
float SceneryObject::getScale(){return scale;}
// Set the image id to draw for this scenery
void SceneryObject::setImageID(int id){
	imageID = id;
}
int SceneryObject::getImageID(){return imageID;}
// Set whether this object collides 
void SceneryObject::setCollides(bool value){
	collides = value;
}
bool SceneryObject::getCollides(){return collides;}
// Get next pointer
SceneryObject* SceneryObject::getNext(){ return next;}
void SceneryObject::setNext(SceneryObject* n){next = n;}

// Returns scenery collision rec
Rec* SceneryObject::getCollisionRec(){return collisionRec;}


// Fix collision rec location 
void SceneryObject::fixCollRec(){
	if (collisionRec){
		collisionRec->setLocation(locX - originX, locY - originY);
		collisionRec->setSize(width, height);
	}
}

// Update game state of the scenery object
void SceneryObject::update(float deltaTime, Handlers* handlers){
	// Nothing to do 
}

// Update scenery input 
void SceneryObject::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH, Handlers* handlers){
	// Nothing to do 
}


// Draw object to the screen
void SceneryObject::draw(GLHandler* mgl, GameAtlas* mGame){
	mGame->draw(mgl,imageID, locX, locY, scale, rotation, originX, originY);
}


// Draw object ui elements 
void SceneryObject::drawUI(GLHandler* mgl, UIAtlas* mUI){
	// Nothing to do 
}