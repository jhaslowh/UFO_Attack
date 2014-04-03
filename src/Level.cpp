#include "Level.h"

Level::Level(){
	player = NULL;
	ground = NULL;
	sceneryHandler = NULL;
	npcHandler = NULL;
	projHandler = NULL;
	loaded = false;
	victory = false;
}
Level::~Level(){
	delete player;
	delete ground;
	delete sceneryHandler;
	delete projHandler;
	delete npcHandler;
}

// initialize level
void Level::init(float screen_width, float screen_height, SaveData* savedata){
	// Setup sky 
	sky.init(screen_width, screen_height);
	// Create player 
	player = new Player(savedata);
	player->init(screen_width, screen_height);
	// Initialize camera 
	camera.init(screen_width, screen_height);
	// Create scenery handler 
	sceneryHandler = new SceneryHandler();
	// Create npc handler
	npcHandler = new NPCHandler();
	// Create ground 
	ground = new Ground(GROUND_CEMENT);
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
	handlers.player = player;
	handlers.projHandler = projHandler;
	handlers.npcHandler = npcHandler;

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

	npcHandler->add(new NPCSoldier(40.0f, 250.0f));

	// Set level top and bottom 
	levelProps.setLevelBottom(ground->getBottomMost());
	levelProps.setLevelTop(ground->getTopMost() - 500.0f);
	levelProps.setEnemyCount(1);
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
	int n = npcHandler->update(deltaTime, &handlers);
	// Check for victory
	if (levelProps.getEnemyCount() != 0 && (n/levelProps.getEnemyCount()) < .1f)
		victory = true;
	projHandler->updateProjectiles(deltaTime, &handlers);

	player->update(deltaTime, &handlers);
	player->checkCollision(&handlers);
	player->update2(deltaTime, &handlers);

	camera.update(deltaTime);
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

	// ------------------------------
	// Draw lights 
	mgl->lightBegin(sky.getLightValue(),sky.getLightValue(),sky.getLightValue());

	mgl->setViewMatrix(camera.getMatrix());
	mgl->setFlatColor(COLOR_WHITE);
	sceneryHandler->drawLight(mgl, &gameAtlas);
	projHandler->drawLight(mgl, &gameAtlas);
	player->drawLight(mgl);

	mgl->lightEnd();
	
	// ------------------------------
	// Bind Game Atlas buffers
	gameAtlas.bindBuffers(mgl);
	gameAtlas.bindTextureFast(mgl);

	// Enable lights 
	mgl->enableLight(true);

	// Draw sky 
	mgl->setFlatColor(COLOR_WHITE);
	mgl->setViewMatrix(glm::mat4());
	sky.draw(mgl, &gameAtlas);
	
	// Draw level 
	mgl->setViewMatrix(camera.getMatrix());
	mgl->setFlatColor(COLOR_WHITE);
	sceneryHandler->draw(mgl, &gameAtlas);
	npcHandler->draw(mgl, &gameAtlas);
	projHandler->draw(mgl, &gameAtlas);			
	player->draw(mgl);							
	ground->draw(mgl);							
	
	// Disable lights 
	mgl->enableLight(false);

	// ------------------------------
	// Draw player hud
	mgl->setViewMatrix(glm::mat4());
	player->drawHud(mgl);
}

// Draw level 
void Level::drawUI(GLHandler* mgl, UIAtlas* mAtlas){
	if (!loaded)
		return;

	sceneryHandler->drawUI(mgl, mAtlas);
}

// Returns current victory state
bool Level::getVictory(){
	return victory;
}
