#include "Level.h"

using namespace std;

Level::Level(){
	player = NULL;
	ground = NULL;
	sceneryHandler = NULL;
	npcHandler = NULL;
	projHandler = NULL;
	explHandler = NULL;
	loaded = false;
	victory = false;
}

Level::~Level(){
	delete player;
	delete ground;
	delete sceneryHandler;
	delete projHandler;
	delete npcHandler;
	delete explHandler;
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
	// Create explosion handler
	explHandler = new ExplHandler();

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
	handlers.explHander = explHandler;

	// Load level from file 
	loadLevel(&handlers, savedata->levelToLoad);
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

	projHandler->updateProjectiles(deltaTime, &handlers);
	explHandler->update(deltaTime);
	
	// Set player enemy size for hud
	player->update(deltaTime, &handlers);
	player->checkCollision(&handlers);
	player->update2(deltaTime, &handlers);

	sceneryHandler->update(deltaTime, &handlers);
	
	// Update enemies and check for victory 
	float n = (float)npcHandler->update(deltaTime, &handlers);
	if (levelProps.getEnemyCount() != 0 && (n/levelProps.getEnemyCount()) < .1f)
		victory = true;
	// Tell player the enemy count to draw 
	player->setEnemyBarScale(n/levelProps.getEnemyCount());

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
	explHandler->draw(mgl, &gameAtlas);
	player->draw(mgl);							
	ground->draw(mgl);							
	
	// Disable lights 
	mgl->enableLight(false);

	// ------------------------------
	// Draw player hud
	mgl->setViewMatrix(glm::mat4());
	player->drawHud(mgl);
}

// Draw level ui
// Note: this will not use the level's Camera view
void Level::drawUI(GLHandler* mgl, UIAtlas* mAtlas){
	if (!loaded)
		return;

	sceneryHandler->drawUI(mgl, mAtlas);
	player->drawUI(mgl, mAtlas);
}

// Returns current victory state
bool Level::getVictory(){
	return victory;
}
