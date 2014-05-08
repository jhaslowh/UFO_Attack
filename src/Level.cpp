#include "Level.h"

using namespace std;

Level::Level(){
	player = NULL;
	ground = NULL;
	sceneryHandler = NULL;
	npcHandler = NULL;
	projHandler = NULL;
	partHandler = NULL;
	explHandler = NULL;
	loaded = false;
	victory = false;
}

Level::~Level(){
	delete player;
	player = NULL;
	delete ground;
	ground = NULL;
	delete sceneryHandler;
	sceneryHandler = NULL;
	delete projHandler;
	projHandler = NULL;
	delete partHandler;
	partHandler = NULL;
	delete npcHandler;
	npcHandler = NULL;
	delete explHandler;
	explHandler = NULL;
}

// initialize level
void Level::init(float screen_width, float screen_height, SaveData* savedata, void * soundHandler){
	// Setup sky 
	sky.init(screen_width, screen_height);
	// Create player 
	player = new Player(savedata);
	player->init(screen_width, screen_height, savedata);
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
	// Create Particle handler
	partHandler = new ParticleHandler();
	// Create explosion handler
	explHandler = new ExplHandler();
	// Create Script Handler
	scriptHandler = new ScriptHandler(&handlers, savedata->levelToLoad);

	// Give screen size to level properties 
	levelProps.setScreenWidth(screen_width);
	levelProps.setScreenHeight(screen_height);
	levelProps.screenRec.setWidth(screen_width + 100.0f);
	levelProps.screenRec.setHeight(screen_height + 100.0f);
	// Set particles reference to screen rec
	partHandler->screenRec = &(levelProps.screenRec);

	// Set Handler references 
	handlers.ground = ground;
	handlers.sceneryHandler = sceneryHandler;
	handlers.camera = &camera;
	handlers.levelProps = &levelProps;
	handlers.player = player;
	handlers.projHandler = projHandler;
	handlers.npcHandler = npcHandler;
	handlers.explHander = explHandler;
	handlers.partHandler = partHandler;
	handlers.soundHandler = soundHandler;
	handlers.sky = &sky;
	handlers.scriptHandler = &scriptHandler;

	// Load level from file 
	loadLevel(&handlers, savedata->levelToLoad);
	


	
	// Update once to fix level image before tutorial lock
	sky.setTimeOfDay(9.0f);
	update(0.0f);
	
	// Setup tutorial system
	tutSys.init(screen_width, screen_height, savedata);
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
	tutSys.update(deltaTime, &handlers);

	if (!tutSys.getLock()){
		// Set screen rec area 
		levelProps.screenRec.setLocation(
			camera.toLevelX(0.0f) - 50.0f,
			camera.toLevelY(0.0f) - 50.0f);

		// Update sky 
		sky.update(deltaTime);

		// Update projectiles and explosions 
		projHandler->updateProjectiles(deltaTime, &handlers);
		explHandler->update(deltaTime);
	
		// Update player
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

		partHandler->update(deltaTime);

		camera.update(deltaTime);
		scriptHandler->updateScripts(deltaTime);
	}
}

// Update input
void Level::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	tutSys.updateInput(mKeyH, mMouseH, &handlers);

	if (!tutSys.getLock()){
		sceneryHandler->updateInput(mKeyH, mMouseH, &handlers);
		player->updateInput(mKeyH, mMouseH, &handlers);
	}
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

	// Draw actual lights 
	mgl->setViewMatrix(camera.getMatrix());
	mgl->setFlatColor(COLOR_WHITE);
	explHandler->draw(mgl, &gameAtlas);
	sceneryHandler->drawLight(mgl, &gameAtlas);
	projHandler->drawLight(mgl, &gameAtlas);
	player->drawLight(mgl); // Draw last, it binds its own buffer 

	// Draw clipping objects for light 
	ground->drawLight(mgl);

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

	partHandler->draw(mgl, &gameAtlas);
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

	tutSys.draw(mgl, mAtlas);
}

// Returns current victory state
bool Level::getVictory(){
	return victory;
}

// Call to skip tutorial
void Level::skipTut(){
	tutSys.setTutsShown();
}