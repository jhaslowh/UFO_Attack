#include "Level.h"

Level::Level(){
	player = new Player();
	gameAtlas = new GameAtlas();
	ground = NULL;
}
Level::~Level(){
	if (player != NULL)
		delete player;
	if (ground != NULL)
		delete ground;
	if (gameAtlas != NULL)
		delete gameAtlas;
}

// Get reference to ground 
Ground* Level::getGround(){
	return ground;
}

// initialize level
void Level::init(float screen_width, float screen_height){
	player->init();
	player->ufo->setLocation(100.0f,200.0f);

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

	// Set Handler references 
	handlers.ground = ground;
}

// Load level (use for textures)
void Level::load(TextureAtlas* mAtlas){
	player->load();
	ground->load();
	gameAtlas->init();
}

// Update level state
void Level::update(float deltaTime){
	player->update(deltaTime, &handlers);
	player->checkCollision(&handlers);
	player->resolveCollision();
}

// Update input
void Level::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	player->updateInput(mKeyH, mMouseH);
}

// Draw level 
void Level::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	gameAtlas->bindBuffers(mgl);
	gameAtlas->bindTexture(mgl);

	// Set flat color back to white 
	GLfloat color[4] = {1.0f,1.0f,1.0f,1.0f};
	mgl->setFlatColor(color);

	player->draw(mgl, gameAtlas);
	ground->draw(mgl);
}