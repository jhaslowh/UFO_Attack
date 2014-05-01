#include "Particle.h"


Particle::Particle()
{
	// Drawing properties 
	imageId = 0;
	locX = locY = 0.0f;
	originX = originY = 0.0f;
	scale = 1.0f;
	rotation = 0.0f;

	// Movement
	speed = 0.0f;
	direcX = direcY = 0.0f;
	rotationSpeed = 0.0f;
	scaleSpeed = 0.0f;
	
	// Animation
	animated = false;
	loops = false;
	cframe = 0;
	frames = 0;
	frameTime = 0.0f;
	cframeTime = 0.0f;

	// State
	lifeTime = 10.0f;
	clifeTime = 0.0f;
	valid = false;
}

void Particle::clone(Particle* p){
	// Drawing properties 
	imageId = p->imageId;
	locX = p->locX;
	locY = p->locY;
	originX = p->originX;
	originY = p->originY;
	scale = p->scale;
	rotation = p->rotation;

	// Movement
	speed = p->speed;
	direcX = p->direcX;
	direcY = p->direcY;
	rotationSpeed = p->rotationSpeed;
	scaleSpeed = p->scaleSpeed;
	
	// Animation
	animated = p->animated;
	loops = p->loops;
	cframe = p->cframe;
	frames = p->frames;
	frameTime = p->frameTime;
	cframeTime = p->cframeTime;

	// State
	lifeTime = p->lifeTime;
	clifeTime = p->clifeTime;
	valid = p->valid;
}

// Getters and setters 
void Particle::setImageId(int i){imageId = i;}
int Particle::getImageId(){return imageId;}
void Particle::setLoc(float x, float y){locX = x; locY = y;}
void Particle::setX(float x){locX = x;}
float Particle::getX(){return locX;}
void Particle::setY(float y){locY = y;}
float Particle::getY(){return locY;}
void Particle::setOrigin(float x, float y){originX = x; originY = y;}
void Particle::setOriginX(float x){originX = x;}
float Particle::getOriginX(){return originX;}
void Particle::setOriginY(float y){originY = y;}
float Particle::getOriginY(){return originY;}
void Particle::setScale(float s){scale = s;}
float Particle::getScale(){return scale;}
void Particle::setRotation(float r){rotation = r;}
float Particle::getRotation(){return rotation;}
void Particle::setSpeed(float s){speed = s;}
float Particle::getSpeed(){return speed;}
void Particle::setDirec(float x, float y){direcX = x; direcY = y;}
void Particle::setRotSpeed(float r){rotationSpeed = r;}
float Particle::getRotSpeed(){return rotationSpeed;}
void Particle::setScaleSpeed(float s){scaleSpeed = s;}
float Particle::getScaleSpeed(){return scaleSpeed;}
void Particle::setAnimates(bool a){animated = a;}
bool Particle::getAnimates(){return animated;}
void Particle::setLoops(bool l){loops = l;}
bool Particle::getLoops(){return loops;}
void Particle::setFrames(int f){frames = f;}
int Particle::getFrames(){return frames;}
void Particle::setFrameTime(float ft){frameTime = ft;}
float Particle::getFrameTime(){return frameTime;}
// This will set the amout of time the particle is active for.
// Max is 10 seconds. 
void Particle::setLifeTime(float l){
	if (l <= 10.0f) 
		lifeTime = l;
}
float Particle::getLifeTime(){return lifeTime;}
void Particle::setValid(bool v){valid = v;}
float Particle::getValid(){return valid;}

// Update particle state 
void Particle::update(float deltaTime){
	if (valid){
		// Update movement 
		locX += direcX * speed * deltaTime;
		locY += direcY * speed * deltaTime;
		scale += scaleSpeed * deltaTime;
		if (scale <= 0.0f) valid = false;
		rotation += rotationSpeed * deltaTime;

		// Update lifetime 
		clifeTime += deltaTime;
		if (clifeTime >= lifeTime)
			valid = false;

		// Update animation
		if (animated){
			cframeTime += deltaTime;
			if (cframeTime >= frameTime){
				cframe++;
				cframeTime = 0.0f;
				if (cframe >= frames){
					if (loops)
						cframe = 0;
					else 
						valid = false;
				}
			}
		}
	}
}

// Draw particle 
void Particle::draw(GLHandler* mgl, GameAtlas* mAtlas){
	if (valid){
		mAtlas->draw(mgl,imageId+cframe,locX,locY,scale,rotation,originX,originY);
	}
}

// Resets current state
void Particle::reset(){
	// Drawing properties 
	imageId = 0;
	locX = locY = 0.0f;
	originX = originY = 0.0f;
	scale = 1.0f;
	rotation = 0.0f;

	// Movement
	speed = 0.0f;
	direcX = direcY = 0.0f;
	rotationSpeed = 0.0f;
	scaleSpeed = 0.0f;
	
	// Animation
	animated = false;
	loops = false;
	cframe = 0;
	frames = 0;
	frameTime = 0.0f;
	cframeTime = 0.0f;

	// State
	lifeTime = 10.0f;
	clifeTime = 0.0f;
	valid = true;
}
