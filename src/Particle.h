#pragma once
#include "GLHandler.h"
#include "GameAtlas.h"

class Particle
{
	// Drawing properties 
	int imageId;
	float locX, locY;
	float originX, originY;
	float scale;
	float rotation;

	// Movement
	float speed;
	float direcX, direcY;
	float rotationSpeed;
	float scaleSpeed;

	// Animation
	bool animated;
	bool loops;
	int cframe;
	int frames;
	float frameTime;
	float cframeTime;

	// State
	float lifeTime;
	float clifeTime;
	bool valid;

public:
	Particle();

	void clone(Particle* p);

	// Getters and setters 
	void setImageId(int i);
	int getImageId();
	void setLoc(float x, float y);
	void setX(float x);
	float getX();
	void setY(float y);
	float getY();
	void setOrigin(float x, float y);
	void setOriginX(float x);
	float getOriginX();
	void setOriginY(float y);
	float getOriginY();
	void setScale(float s);
	float getScale();
	void setRotation(float r);
	float getRotation();
	void setSpeed(float s);
	float getSpeed();
	void setDirec(float x, float y);
	void setRotSpeed(float r);
	float getRotSpeed();
	void setScaleSpeed(float s);
	float getScaleSpeed();
	void setAnimates(bool a);
	bool getAnimates();
	void setLoops(bool l);
	bool getLoops();
	void setFrames(int f);
	int getFrames();
	void setFrameTime(float ft);
	float getFrameTime();
	// This will set the amout of time the particle is active for.
	// Max is 10 seconds. 
	void setLifeTime(float l);
	float getLifeTime();
	void setValid(bool v);
	float getValid();

	// Update particle state 
	void update(float deltaTime);

	// Draw particle 
	void draw(GLHandler* mgl, GameAtlas* mAtlas);

	// Resets current state
	void reset();
};

