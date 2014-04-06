#include "Level.h"

using namespace std;

Level::Level(){
	player = NULL;
	ground = NULL;
	sceneryHandler = NULL;
	npcHandler = NULL;
	projHandler = NULL;
	loaded = false;
	victory = false;
	loadData = false;
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

	// Set player spawn location
	loadLevelData(savedata->levelToLoad);
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
	if (levelProps.getEnemyCount() != 0 && (n/levelProps.getEnemyCount()) < .1f && loadData)
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

//Load Level Data
void Level::loadLevelData(std::string levelFile)
{
	bool debug = false;
	string line;

	levelFile.append(".txt");
	levelFile.insert(0, ".\\Levels\\");
	ifstream myfile (levelFile);

	if(myfile.is_open())
	{
		cout << "opening level now...\n";
		cout << "assuming correct format...\n";
		getline(myfile, line);
		getline(myfile, line);
		while(!myfile.eof())
		{
			getline(myfile, line);
			if(line.compare("PlayerX")==0)
			{
				getline(myfile, line);
				float tempX = (float)atoi(line.c_str());
				getline(myfile, line);
				levelProps.setPlayerSpawn(tempX,(float)atoi(line.c_str()));
				player->ufo->setLocation(levelProps.getPlayerSpawnX(), levelProps.getPlayerSpawnY());
			}
			else if(line.compare("LevelLeft")==0)
			{
				getline(myfile, line);
				levelProps.setLevelLeft((float)atoi(line.c_str()));
			}
			else if(line.compare("LevelRight")==0)
			{
				getline(myfile, line);
				levelProps.setLevelRight((float)atoi(line.c_str()));
			}
			/*else if(line.compare("LevelTop")==0)
			{
				getline(myfile, line);
				levelProps.setLevelTop((float)atoi(line.c_str()));
			}
			else if(line.compare("LevelBottom")==0)
			{
				getline(myfile, line);
				levelProps.setLevelBottom((float)atoi(line.c_str()));
			}*/
			else if(line.compare("ground")==0)
			{
				getline(myfile, line);
				getline(myfile, line);
				ground->setType((int)atoi(line.c_str()));
				getline(myfile, line);
				while(line.compare("end")!=0)
				{
					if (debug) cout << "new ground point\n";
					size_t pos = 0;
					string storage[2];
					std::string delimiter = ";";
					int counter = 0;
					while ((pos = line.find(delimiter)) != std::string::npos) 
					{
						storage[counter] = line.substr(0, pos);
						line.erase(0, pos + delimiter.length());
						counter++;
					}
					storage[counter] = line;
					ground->add(new Point((float)atoi(storage[0].c_str()),(float)atoi(storage[1].c_str())));
					if (debug) cout << "X: " << (float)atoi(storage[0].c_str()) << " Y: " << (float)atoi(storage[1].c_str()) << " \n";
					getline(myfile, line);
				}
			}
			else if(line.compare("scenery")==0)
			{
				SceneryObject* obj;
				if (debug) cout << "enter scenery" << std::endl;

				getline(myfile, line);
				//x y width height rotation scale imageid collides stopplayer
				getline(myfile, line);

				while(line.compare("end")!=0)
				{
					//getline(myfile, line);
					if (debug) cout << "SceneryLine: " << line << std::endl;
					size_t pos = 0;
					string storage[11];
					std::string delimiter = ";";
					int counter = 0;
					while ((pos = line.find(delimiter)) != std::string::npos) 
					{
						storage[counter] = line.substr(0, pos);
						line.erase(0, pos + delimiter.length());
						counter++;
					}
					storage[counter] = line;
					if(storage[9].compare("tree")==0)
					{
						obj = (SceneryObject*)new Tree();
						obj->setLocation((float)atoi(storage[0].c_str()),(float)atoi(storage[1].c_str()));
						sceneryHandler->add(obj);
						if (debug) cout << "tree" << std::endl;
					}
					else if(storage[9].compare("fence")==0)
					{
						obj = (SceneryObject*)new Fence();
						obj->setLocation((float)atoi(storage[0].c_str()),(float)atoi(storage[1].c_str()));
						sceneryHandler->add(obj);
					}
					else if(storage[9].compare("crate")==0)
					{
						obj = (SceneryObject*)new Crate();
						obj->setLocation((float)atoi(storage[0].c_str()),(float)atoi(storage[1].c_str()));
						sceneryHandler->add(obj);
					}
					else if(storage[9].compare("longcrate")==0)
					{
						obj = (SceneryObject*)new LongCrate();
						obj->setLocation((float)atoi(storage[0].c_str()),(float)atoi(storage[1].c_str()));
						sceneryHandler->add(obj);
					}
					else if(storage[9].compare("tallcrate")==0)
					{
						obj = (SceneryObject*)new TallCrate();
						obj->setLocation((float)atoi(storage[0].c_str()),(float)atoi(storage[1].c_str()));
						sceneryHandler->add(obj);
					}
					else if(storage[9].compare("hayBale")==0)
					{
						obj = (SceneryObject*)new HayBale();
						obj->setLocation((float)atoi(storage[0].c_str()),(float)atoi(storage[1].c_str()));
						sceneryHandler->add(obj);
					}
					if (debug) cout << "looping" << std::endl;
					getline(myfile, line);
				}
			}
			else if(line.compare("signs")==0)
			{
				getline(myfile, line);
				//x y width height rotation scale imageid collides stopplayer
				getline(myfile, line);
				SceneryObject* obj;
				while(line.compare("end")!=0)
				{
					//getline(myfile, line);
					if (debug) cout << "StartLine: " << line << std::endl;
					size_t pos = 0;
					string storage[11];
					std::string delimiter = ";";
					int counter = 0;
					while ((pos = line.find(delimiter)) != std::string::npos) 
					{
						storage[counter] = line.substr(0, pos);
						line.erase(0, pos + delimiter.length());
						counter++;
					}
					if (debug) cout << "Line: " << line << std::endl;
					storage[counter] = line;
					//if((float)atoi(storage[0].c_str()))
					obj = (SceneryObject*)new Sign();
					((Sign*)obj)->setText(storage[10]);
					if (debug) cout << "Sign text: " << storage[10] << std::endl;
					obj->setLocation((float)atoi(storage[0].c_str()),(float)atoi(storage[1].c_str()));
					sceneryHandler->add(obj);
					getline(myfile, line);
				}
			}
			else if(line.compare("npcs")==0)
			{
				if (debug) std::cout << "parsing npcs\n";
				int npcCounter=0;
				getline(myfile, line);
				getline(myfile, line);
				while(line.compare("end")!=0)
				{
					size_t pos = 0;
					string storage[3];
					std::string delimiter = ";";
					int counter = 0;
					while ((pos = line.find(delimiter)) != std::string::npos) 
					{
						storage[counter] = line.substr(0, pos);
						line.erase(0, pos + delimiter.length());
						counter++;
					}
					storage[counter] = line;
					if(storage[2].compare("soldier")==0)
					{
						npcHandler->add(new NPCSoldier((float)atoi(storage[0].c_str()),(float)atoi(storage[1].c_str())));
						if (debug) cout << "made npc" << std::endl;
					}
					npcCounter++;
					getline(myfile, line);
					if (debug) cout << "NPC Counter: " << npcCounter << std::endl;
				}
				levelProps.setEnemyCount(npcCounter);
			}
			levelProps.setLevelBottom(ground->getBottomMost());
			levelProps.setLevelTop(ground->getTopMost() - 500.0f);

		}
		myfile.close();
		//npcHandler->add(new NPCSoldier(40.0f, 100.0f));
	}
	else
	{
		cout << "level file not found\n";
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

		npcHandler->add(new NPCSoldier(40.0f, 100.0f));

		// Set level top and bottom 
		levelProps.setLevelBottom(ground->getBottomMost());
		levelProps.setLevelTop(ground->getTopMost() - 500.0f);
	}
	loadData = true;
}

// Returns current victory state
bool Level::getVictory(){
	return victory;
}
