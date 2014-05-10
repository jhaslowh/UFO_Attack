#include "Projectile.h"
using namespace std;

Projectile::Projectile()
{
	initValues();
}

Projectile::~Projectile(){

}

// Clone all the properties from the sent projectiles into this one
void Projectile::clone(Projectile* p){
	projectileType = p->projectileType;
	previousX = p->previousX;
	previousY = p->previousY;
	currentX = p->currentX;
	currentY = p->currentY;
	xVector = p->xVector; 
	yVector = p->yVector;
	mass = p->mass; 
	size = p->size; 
	negligence = p->negligence;
	doesExplode = p->doesExplode;
	diesOnImpact = p->diesOnImpact;
	imageId = p->imageId;
	imageGlowId = p->imageGlowId;
	offsetX = p->offsetX;
	offsetY = p->offsetY;
	glowOffsetX = p->glowOffsetX;
	glowOffsetY = p->glowOffsetY;
	rotation = p->rotation;
	damage = p->damage;
	firedBy = p->firedBy;
	drawColor[0] = p->drawColor[0];
	drawColor[1] = p->drawColor[1];
	drawColor[2] = p->drawColor[2];
	drawColor[3] = p->drawColor[3];
	smokeTrail = p->smokeTrail;
	partTime = p->partTime;
	
	alive = p->alive;

	explosion.cloneE(&(p->explosion));
}


// Returns a clone pointer of this projectile 
void* Projectile::clone(){
	Projectile* p = new Projectile();
	// Physics 
	p->projectileType = projectileType;
	p->previousX = previousX;
	p->previousY = previousY;
	p->currentX = currentX;
	p->currentY = currentY;
	p->xVector = xVector;
	p->yVector= yVector;
	p->speed = speed;
	p->mass = mass; 
	p->size = size; 
	p->negligence = negligence;
	p->damage = damage;
	p->firedBy = firedBy;

	// Drawing properties 
	p->imageId = imageId;
	p->imageGlowId = imageGlowId;
	p->offsetX = offsetX;
	p->offsetY = offsetY;
	p->glowOffsetX = glowOffsetX;
	p->glowOffsetY = glowOffsetY;
	p->drawProj = drawProj;
	p->rotation = rotation;
	p->drawColor[0] = drawColor[0];
	p->drawColor[1] = drawColor[1];
	p->drawColor[2] = drawColor[2];
	p->drawColor[3] = drawColor[3];

	// Particles
	p->smokeTrail = smokeTrail;
	p->partTime = partTime;

	// States 
	p->alive = alive;
	p->doesExplode = doesExplode;
	p->explosion.cloneE(&explosion);
	p->diesOnImpact = diesOnImpact;

	return p;
}

//UpdateProjectile does the heavier stuff for projectiles with complicated movement, and will handle collision detection
//This will act as a default in case a projectile doesn't have its own updateProjectile method
void Projectile::updateProjectile(float deltaTime, Handlers* handlers)
{
	if(projectileType==3)
	{
		previousY = currentY;
		previousX = currentX;
		yVector+=10*size*deltaTime;
		xVector-=5*size*deltaTime;
		//There should be a very large section for collision based interactions
		//Stuff like rolling on the ground and bouncing
		currentX+=xVector*deltaTime;
		currentY+=yVector*deltaTime;
	}
	else
	{
		previousY = currentY;
		previousX = currentX;
		yVector+=1*size;
		//xVector+=.25*size;

		//There should be a very large section for collision based interactions
		//Stuff like rolling on the ground and bouncing
		currentX+=xVector*deltaTime;
		currentY+=yVector*deltaTime;
	}
}

//This method does not need to be overloaded for different projectiles, 
//it is the same for every unphysiced projectile
void Projectile::updateNegligableProjectile(float deltaTime)
{
	//cout << "negP";
	previousY = currentY;
	previousX = currentX;
	currentX+=xVector*deltaTime;
	currentY+=yVector*deltaTime;
}

//This will need to have some cases for each different kind of projectile, 
//but there are some basic reasons to be negligable here
void Projectile::determineNegligance()
{
	//A beam typed weapon would not be affected by gravity or wind resistance
	if(projectileType == PROJT_BULLET || projectileType == PROJT_BEAM || projectileType == PROJT_TEST)
	{
		negligence = true; 
	}

	//This is an extreme example of a case at which a projectile has enough 
	//inertia that it will take its course before noticable change to its trajectory
	else if(((xVector+yVector)*mass) >= 50000)
		negligence = true; 

	//A sufficiently small projectile that is moving fast enough will 
	//not be affected by wind resistance and can most likely fulfill 
	//its course before gravity has any noticable effect
	else if(size < 1 && (xVector+yVector) >= 20000)
		negligence = true; 
	
	//Need to figure out all the collision stuff, but here should be
	//if(projectile == Colliding)
	//  negligence = false;
	
}

// Check projectile collision 
void Projectile::checkCollision(float deltaTime, Handlers* handlers){
	// Check if projectile should be drawn 
	Camera2D* cam = (Camera2D*)handlers->camera;
	LevelProperties* levelProps = (LevelProperties*)handlers->levelProps;
	if (cam->toScreenX(currentX) > -50 && cam->toScreenX(currentX) < levelProps->getScreenWidth() + 50 &&
		cam->toScreenY(currentY) > -50 && cam->toScreenY(currentY) < levelProps->getScreenHeight() + 50)
		drawProj = true;
	else 
		drawProj = false;

	// Fix projectile rotation 
	rotation = (180.0f/3.14159f) * atan2(currentY - previousY, currentX - previousX);

	// Check if projectile is outside level bounds, and if so, kill projectile.
	if (currentX < levelProps->getLevelLeft() - 500 ||
		currentX > levelProps->getLevelRight() + 500 ||
		currentY > levelProps->getLevelBottom()){
		alive = false;
	}

	// Ground collision 
	Point* itr = handlers->ground->getPoints();
	Point p;
	if (itr != NULL){
		while (itr->next != NULL){
			// Check if player is close to point
			if ((*itr).getX() - 50 <= currentX && (*(itr->next)).getX() + 50 >= currentX){
				if (checkSegSeg(
					Point(currentX,currentY), Point(previousX,previousY), 
					*itr, *(itr->next), &p)){
					collide(&p, handlers, P_GROUND_COLL);
					break;
				}
			}
			itr = itr->next;
		}
	}

	// Update particles 
	if (smokeTrail){
		partTime += deltaTime;
		if (partTime >= .005f){
			partTime = 0.0f;
			Particle* p = ((ParticleHandler*)handlers->partHandler)->add(
				GI_SMOKE3,	// Image
				currentX,currentY,	// Location
				10.0f,10.0f,// Origin
				0.0f,0.0f,	// Direction
				0.0f,		// Speed
				1.0f,		// Life
				((((rand()%100)/100.0f)*2.0f)-1.0f)*100.0f,		// Rotation speed
				((rand()%100)/100.0f)*-2.0f - 2.0f);		// Scale speed 

			if (p != NULL) p->setRotation(((rand()%100)/100.0f)*360.0f);
		}
	}
}

// Draw projectile to screen
void Projectile::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	if (alive && drawProj){
		mgl->setFlatColor(drawColor);
		mAtlas->draw(mgl, imageId, currentX, currentY, 1.0f, rotation, offsetX, offsetY);
	}
}

// Draw projectile light to screen
void Projectile::drawLight(GLHandler* mgl, TextureAtlas* mAtlas){
	if (alive && drawProj && imageGlowId != -1){
		mgl->setFlatColor(drawColor);
		mAtlas->draw(mgl, imageGlowId, currentX, currentY, 1.0f, rotation, glowOffsetX, glowOffsetY);
	}
}

// Called when projectile collides with something
// CollType 
// 1 = player collision
// 2 = ground collision
// 3 = enemy collision 
//
// p = point of collision 
void Projectile::collide(Point* p, Handlers* handlers, int collType)
{
	// Please do collide stuff here, maybe set a variable for what 
	// it collides with, player/enemy/ground, and what side it collides on.

	// Add explosion to explosion list if explodes 
	if (doesExplode){
		// Reset the projectiles location
		explosion.setLocation(p->getX(), p->getY());
		// Set fired by for projectile 
		if (firedBy == PFB_PLAYER) explosion.setType(PLAYER_EXP);
		else explosion.setType(ENEMY_EXP);
		// Add to handler list 
		((ExplHandler*)handlers->explHander)->add(&explosion);

		SoundHandler * sh = (SoundHandler*)handlers->soundHandler;
		sh->playSoundEffect(SE_ROCKET_EXPLODE_SOUND);
	}

	// Kill if dies on impact
	if (diesOnImpact){
		alive = false;
	}
}

short Projectile::getProjectileType(){return projectileType;}
float Projectile::getCurrentX(){return currentX;}
float Projectile::getCurrentY(){return currentY;}
float Projectile::getPrevX(){return previousX;}
float Projectile::getPrevY(){return previousY;}
bool Projectile::getNegligence(){return negligence;}
bool Projectile::getAlive(){return alive;}
float Projectile::getDamage(){return damage;}
int Projectile::getFiredBy(){return firedBy;}
Explosion Projectile::getExplosion(){return explosion;}
Explosion* Projectile::getExplRef(){return &explosion;}

void Projectile::setSize(int newSize){size = newSize;}
void Projectile::setType(short type){projectileType = type;}
void Projectile::setAlive(bool value){alive = value;}
void Projectile::setImageId(int value){imageId = value;}
void Projectile::setImageGlowId(int value){imageGlowId = value;}
void Projectile::setPosition(float x, float y){
	currentX = x, currentY = y;
	previousX = currentX, previousY = currentY;
}
void Projectile::setOffset(float x, float y){offsetX = x; offsetY = y;}
void Projectile::setGlowOffset(float x, float y){glowOffsetX = x; glowOffsetY = y;}
void Projectile::setDamage(float value){damage = value;}
void Projectile::setFiredBy(int value){firedBy = value;}
void Projectile::setExplodes(bool value){doesExplode = value;}
void Projectile::setDrawColor(GLfloat* color){
	drawColor[0] = color[0];
	drawColor[1] = color[1];
	drawColor[2] = color[2];
	drawColor[3] = color[3];
}
void Projectile::setDrawColor(float r, float g, float b, float a){
	drawColor[0] = r;
	drawColor[1] = g;
	drawColor[2] = b;
	drawColor[3] = a;
}
void Projectile::setExplosion(Explosion e){
	explosion.cloneE(&e);
}
void Projectile::setSmokeTrail(bool value){smokeTrail = value;}
void Projectile::setSpeed(int s){speed = s;}
void Projectile::setDirec(float x, float y){
	xVector = speed*x;
	yVector = speed*y;
}

// Setup basic values for all variables 
void Projectile::initValues(){
	projectileType = PROJT_TEST;
	previousX = 0.0f;
	previousY = 0.0f;
	currentX = 0.0f;
	currentY = 0.0f;
	xVector = 0.0f;
	yVector = 0.0f;
	speed = 200;
	mass = 0;
	size = 0;
	negligence = false;
	alive = false;
	doesExplode = false;
	diesOnImpact = true;
	drawProj = false;
	imageId = 0;
	imageGlowId = -1;
	offsetX = offsetY = glowOffsetX = glowOffsetY = 0;
	rotation = 0;
	damage = 0.0f;
	firedBy = PFB_ENEMY;
	drawColor[0] = 1.0f;
	drawColor[1] = 1.0f;
	drawColor[2] = 1.0f;
	drawColor[3] = 1.0f;
	smokeTrail = false;
	partTime = 0.0f;
}