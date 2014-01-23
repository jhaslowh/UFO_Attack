#pragma once
#include "Rec.h"
#include "GLHandler.h"
#include "GameAtlas.h"
#include "Handlers.h"

class SceneryObject
{
protected:

	float locX, locY;
	float width, height;
	float originX, originY;
	float rotation;
	float scale;
	int imageID;
	bool collides;
	Rec* collisionRec;

public:
	SceneryObject();
	virtual ~SceneryObject();

	// Getters and setters 

	// Set the location of the scenerey 
	void setLocation(float x, float y);
	float geX();
	float getY();
	// Set the width and height of the scenery
	void setSize(float w, float h);
	float getWidth();
	float getHeight();
	// Set the origin point of the scenery
	void setOrigin(float x, float y);
	// Set the rotation of the scenery
	void setRotation(float r);
	float getRotation();
	// Set the scale of the scenery
	void setScale(float s);
	float getScale();
	// Set the image id to draw for this scenery
	void setImageID(int id);
	int getImageID();
	// Set whether this object collides 
	void setCollides(bool value);
	bool getCollides();

	// Returns scenery collision rec
	virtual Rec* getCollisionRec();

	// Update game state of the scenery object
	virtual void update(float deltaTime, Handlers* handlers);

	// Draw object to the screen
	virtual void draw(GLHandler* mgl, GameAtlas* mGame);
};

