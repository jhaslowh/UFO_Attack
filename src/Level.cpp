#include "Level.h"

Level::Level(){}
Level::~Level(){
	if (player != NULL)
		delete(player);
	if (ground != NULL)
		delete(ground);
}

// Get reference to ground 
Ground* Level::getGround(){
	return ground;
}

// initialize level
void Level::init(float screen_width, float screen_height){
	player = new Player();
	player->init(screen_width, screen_height);
	ground = new Ground(12);
	int i = -1;

	Point p(0.0f,400.0f);
	ground->setPoint(++i,p);
	
	p.setLocation(20.0f,400.0f);
	ground->setPoint(++i,p);

	p.setLocation(30.0f,500.0f);
	ground->setPoint(++i,p);

	p.setLocation(120.0f,490.0f);
	ground->setPoint(++i,p);

	p.setLocation(180.0f,500.0f);
	ground->setPoint(++i,p);

	p.setLocation(407.0f,568.0f);
	ground->setPoint(++i,p);

	p.setLocation(500.0f,590.0f);
	ground->setPoint(++i,p);
	
	p.setLocation(650.0f,570.0f);
	ground->setPoint(++i,p);

	p.setLocation(1000.0f,510.0f);
	ground->setPoint(++i,p);

	p.setLocation(1240.0f,550.0f);
	ground->setPoint(++i,p);

	p.setLocation(1250.0f,400.0f);
	ground->setPoint(++i,p);

	p.setLocation(1400.0f,400.0f);
	ground->setPoint(++i,p);
}

// Load level (use for textures)
void Level::load(TextureAtlas* mAtlas){
	player->load();
	ground->load();
}

// Update level state
void Level::update(float deltaTime){
	player->update(deltaTime);
	player->checkCollision(ground);
	player->resolveCollision();
}

// Update input
void Level::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	player->updateInput(mKeyH, mMouseH);
}

// Draw level 
void Level::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	player->draw(mgl);
	ground->draw(mgl);
}