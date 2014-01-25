#include "Level.h"

Level::Level(){
	player = new Player();
	gameAtlas = new GameAtlas();
	ground = NULL;
	sceneryHandler = NULL;
}
Level::~Level(){
	delete player;
	delete ground;
	delete gameAtlas;
	delete sceneryHandler;
}

// Get reference to ground 
Ground* Level::getGround(){
	return ground;
}

// initialize level
void Level::init(float screen_width, float screen_height){
	player->init();
	player->ufo->setLocation(100.0f,200.0f);

	sceneryHandler = new SceneryHandler();
	SceneryObject* obj = (SceneryObject*)new Tree();
	obj->setLocation(321.0f,550.0f);
	sceneryHandler->add(obj);
	obj = (SceneryObject*)new Tree();
	obj->setLocation(907.0f,540.0f);
	sceneryHandler->add(obj);
	obj = (SceneryObject*)new Tree();
	obj->setLocation(1124.0f,533.0f);
	sceneryHandler->add(obj);

	ground = new Ground();
	int i = -1;

	ground->add(new Point(0.0f,400.0f));
	ground->add(new Point(20.0f,400.0f));
	ground->add(new Point(30.0f,500.0f));
	ground->add(new Point(120.0f,490.0f));
	ground->add(new Point(180.0f,500.0f));
	ground->add(new Point(407.0f,568.0f));
	ground->add(new Point(500.0f,590.0f));
	ground->add(new Point(650.0f,570.0f));
	ground->add(new Point(1000.0f,510.0f));
	ground->add(new Point(1240.0f,550.0f));
	ground->add(new Point(1250.0f,400.0f));
	ground->add(new Point(1400.0f,400.0f));

	// Set Handler references 
	handlers.ground = ground;
	handlers.sceneryHandler = sceneryHandler;
}

// Load level (use for textures)
void Level::load(){
	player->load();
	ground->load();
	gameAtlas->init();
}

// Update level state
void Level::update(float deltaTime){
	sceneryHandler->update(deltaTime, &handlers);

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

	sceneryHandler->draw(mgl, gameAtlas);
	player->draw(mgl, gameAtlas);
	ground->draw(mgl);
}