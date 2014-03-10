#include "Level.h"

Level::Level(){
	player = NULL;
	ground = NULL;
	sceneryHandler = NULL;
	projHandler = NULL;
	loaded = false;
}
Level::~Level(){
	delete player;
	delete ground;
	delete sceneryHandler;
	delete projHandler;
}

// initialize level
void Level::init(float screen_width, float screen_height){
	// Setup sky 
	sky.init(screen_width, screen_height);
	// Create player 
	player = new Player();
	player->init(screen_width, screen_height);
	// Initialize camera 
	camera.init(screen_width, screen_height);
	// Create scenery handler 
	sceneryHandler = new SceneryHandler();
	// Create ground 
	ground = new Ground();
	// Create proj handler 
	projHandler = new ProjectileHandler();

	// Give screen size to level properties 
	levelProps.setScreenWidth(screen_width);
	levelProps.setScreenHeight(screen_height);

	// Set Handler references 
	handlers.ground = ground;
	handlers.sceneryHandler = sceneryHandler;
	handlers.camera = &camera;
	handlers.levelProps = &levelProps;
	handlers.player = &player;
	handlers.projHandler = projHandler;

	// ------------------------------
	// DEBUG TEST LEVEL
	// Replace with real loading code
	// ------------------------------

	// Set player spawn location 
	levelProps.setPlayerSpawn(100.0f,100.0f);
	player->ufo->setLocation(levelProps.getPlayerSpawnX(), levelProps.getPlayerSpawnY());

	levelProps.setLevelLeft(-500.0f);
	levelProps.setLevelRight(1800.0f);

	SceneryObject* obj = (SceneryObject*)new Tree();
	obj->setLocation(321.0f,550.0f);
	sceneryHandler->add(obj);
	obj = (SceneryObject*)new Tree();
	obj->setLocation(907.0f,540.0f);
	sceneryHandler->add(obj);
	obj = (SceneryObject*)new Tree();
	obj->setLocation(1124.0f,533.0f);
	sceneryHandler->add(obj);

	ground->add(new Point(-1500.0f,500.0f));
	ground->add(new Point(-200.0f,500.0f));
	ground->add(new Point(30.0f,500.0f));
	ground->add(new Point(120.0f,490.0f));
	ground->add(new Point(180.0f,500.0f));
	ground->add(new Point(407.0f,568.0f));
	ground->add(new Point(500.0f,590.0f));
	ground->add(new Point(650.0f,570.0f));
	ground->add(new Point(1000.0f,510.0f));
	ground->add(new Point(1240.0f,550.0f));
	ground->add(new Point(1400.0f,500.0f));
	ground->add(new Point(2500.0f,500.0f));
}

// Load level (use for textures)
void Level::load(GLHandler* mgl){
	gameAtlas.load();
	gameAtlas.setupFastBind(mgl,2);
	player->load(mgl);
	ground->load();

	loaded = true;
}

// Unload level
void Level::unload(){
	gameAtlas.unload();
	player->unload();
	ground->unload();

	loaded = false;
}

// Update level state
void Level::update(float deltaTime){
	sky.update(deltaTime);
	sceneryHandler->update(deltaTime, &handlers);
	projHandler->updateProjectiles(deltaTime);

	player->update(deltaTime, &handlers);
	player->checkCollision(&handlers);
	player->update2(deltaTime, &handlers);

	camera.update(deltaTime);
}

// Update the terrain list
void Level::updateTerrain(float newX, float newY)
{
	ground->add(new Point(newX, newY));
}

// Update input
void Level::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	sceneryHandler->updateInput(mKeyH, mMouseH, &handlers);
	player->updateInput(mKeyH, mMouseH, &handlers);
}

// Draw level 
void Level::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	if (!loaded)
		load(mgl);

	// Bind Game Atlas buffers
	gameAtlas.bindBuffers(mgl);
	gameAtlas.bindTextureFast(mgl);

	// Draw sky 
	sky.draw(mgl, &gameAtlas);

	// Set camera 
	mgl->setViewMatrix(camera.getMatrix());

	// Draw lights 
	mgl->enableLight(true);
	mgl->lightBegin(
		levelProps.getLight()[0], 
		levelProps.getLight()[1],
		levelProps.getLight()[2]);

	// Draw Scenery Lights 
	sceneryHandler->drawLight(mgl, &gameAtlas);

	mgl->lightEnd();

	// Set flat color back to white 
	mgl->setFlatColor(COLOR_WHITE);
	
	sceneryHandler->draw(mgl, &gameAtlas);		// Uses GameAtlas 
	projHandler->draw(mgl, &gameAtlas);			// Uses GameAtlas

	player->draw(mgl);							// Uses PlayerAtlas
	ground->draw(mgl);							// Uses 1 sprite and 1 custom sprite

	mgl->setViewMatrix(glm::mat4());

	// Draw player hud
	player->drawHud(mgl);

	// Disable lights 
	mgl->enableLight(false);
}

// Draw level 
void Level::drawUI(GLHandler* mgl, UIAtlas* mAtlas){
	if (!loaded)
		return;

	sceneryHandler->drawUI(mgl, mAtlas);
}
