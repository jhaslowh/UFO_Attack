#ifdef WIN32
//pragma to remove extra console window under windows
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif

#include "main.h"
using namespace std;

/**
* Called at the begining of the game to load resources 
*/
int init_resources()
{
	printf("Loading Resources...\n");

	soundHandler = new SoundHandler(settings);
	// Set up shaders 
	if (mgl.load((float)settings->getScreenWidth(),(float)settings->getScreenHeight()) == 0){
		cout << "Error setting up OpenGL\n";
		return 0;
	}
	glUseProgram(mgl.program);
	// Setup ortho matrix
	mgl.setOrthoMatrix((float)settings->getScreenWidth(),(float)settings->getScreenHeight());
	// Setup basic projection matrix 
	mgl.setCamera3DMatrix(
		glm::vec3((float)settings->getScreenWidth()*.5f,(float)settings->getScreenHeight()*.5f,
		-((settings->getScreenHeight()/2.0f) / tan((3.14159f * 22.5f)/180.0f))), 
		glm::vec3((float)settings->getScreenWidth()*.5f,(float)settings->getScreenHeight()*.5f,0), 
		(float)settings->getScreenWidth()/(float)settings->getScreenHeight());
	// Set view matrix to identity to avoid rendering problems
	mgl.setViewMatrix(glm::mat4());
	// Turn off light be default
	mgl.enableLight(false);
	// Give gl the resolution
	mgl.setResolution((float)settings->getScreenWidth(),(float)settings->getScreenHeight());

	// Setup gl states 
	mgl.setupGL();

	mUIAtlas = new UIAtlas();
	mUIAtlas->load();
	
	// Make our terminal 
	terminal = new UITerminal();
	terminal->setLocation(5.0f,(float)settings->getScreenHeight() - 35.0f);
	terminal->setSize((float)settings->getScreenWidth() - 10.0f,0.0f);
	terminal->setupHide(HT_VERTICAL,terminal->getY()+100.0f,.2f,false);
	terminal->setCommandFunc(checkCommand);
	terminal->setHidden();
	
	// Setup store items 
	StoreItems::setupStoreItems();

	// Set current screen as test screen 
	screen = (UIScreen*)new IntroLoadScreen();
	screen->init((float)settings->getScreenWidth(),(float)settings->getScreenHeight(), soundHandler);

	printf("Resources loaded\n");
	return 1;
}

/**
* Called when finished to free resources 
*/
void free_resources()
{
	printf("Free Resources...\n");
	// Wait for update thread to finish
	SDL_WaitThread(thread, NULL);

	// Delete gscreens 
	if (gscreen_unload != NULL){
		gscreen_unload->unload();
		delete gscreen_unload;
		gscreen_unload = NULL;
	}
	if (gscreen != NULL){
		gscreen->unload();
		delete gscreen;
		gscreen = NULL;
	}

	// Delete screen
	if (screen != NULL){
		screen->unload();
		delete screen;
		screen = NULL;
	}

	// Delete unload screen
	if (screen_unload != NULL){
		screen_unload->unload();
		delete screen_unload;
		screen_unload = NULL;
	}

	// Unload atlas 
	if (mUIAtlas != NULL) mUIAtlas->unload();
	// Unload program
	glUseProgram(0);
	// Unload GLHandler
	mgl.unload();
	// Disable gl states 
	mgl.endGL();

	// Delete allocations 
	delete mUIAtlas;
	delete terminal;
	delete soundHandler;

	// Save data 
	saveSettings(settings);
	delete settings;
	saveSaveData(savedata);
	delete savedata;

	printf("Resources Freed\n");
}

/** 
 * Update game state 
 */
void onUpdate(){
	// Figure out delta time in seconds 
	// Grab current ticks 
	int mTime = SDL_GetTicks();
	// Get the time since the last update 
	int diff = mTime - lastTime;
	deltaTime = (float)diff / 1000.0f;
	// Set this time as the last time 
	lastTime = mTime;

	// Do main updates if window is visible 
	if (WINDOW_VISIBLE){
		// Show hide terminal
		if (!showTerminal && mKeyH.keyPressed(KEY_TILDE)){
			showTerminal = true;
			terminal->show();
		}
		else if (showTerminal && (mKeyH.keyPressed(KEY_TILDE)
			|| mKeyH.keyPressed(KEY_ESCAPE))){
			showTerminal = false;
			terminal->hide();
		}

		// Update Terminal
		else {
			if (showTerminal) 
				terminal->updateInput(&mKeyH, &mMouseH);
			terminal->update(deltaTime);
		}
		
		// Update Screen 
		if (screen != NULL) {
			// Update screen input 
			if (!showTerminal) {
				if (!screen->updateInputFocus(&mKeyH, &mMouseH))
					screen->updateInput(&mKeyH, &mMouseH);
			}
			// Update screen 
			screen->update(deltaTime);
			// Check if screen needs to be changed 
			changeScreen();
		}

		// Update input 
		// Note: this does not actually grab the input, but
		// runs helper code nessesary for it to work correctly. 
		mMouseH.update();
		mKeyH.update(deltaTime);
	}
}


// Check commands from the terminal
void checkCommand(string line){
	// Command
	string command;
	string args("");

	// Get command and args 
	UITerminal::getCommandAndArgs(&line, &command, &args);

	// -------------- //
	// Check commands 
	// -------------- // 

	// If you want to check a global command, do it here and
	// return so that the screen does not parse the same command. 

	// Check for disable terminal command 
	if (command == "off"){
		terminal->addLine(command, TL_SUCCESS);
		showTerminal = false;
		terminal->hide();

		if (args != "")
			terminal->addLine("Ignoring unrecognized arguments given to command: off", TL_WARNING);

		return;
	}
	// Check for restart command
	else if (command == "restart"){
		// Tell game to restart
		restart = true;
		// Hide terminal
		// (even though context is reset, this will not reset so we must change it)
		showTerminal = false;
		// Tell current context to end 
		running = false;
		return;
	}
	// Check for clear command
	else if (command == "clear"){
		terminal->clear();
		return;
	}
	// Check for help command
	else if (command == "help"){
		terminal->clear();

		if (args == "" || args == "1"){
			terminal->addLine("help [page] : print out help page [1-3]", TL_SUCCESS); 
			terminal->addLine("off : close terminal", TL_SUCCESS); 
			terminal->addLine("restart : restart entire game", TL_SUCCESS); 
			terminal->addLine("clear : clear terminal", TL_SUCCESS); 
			terminal->addLine("version : print out version", TL_SUCCESS); 
			terminal->addLine("screen hide : hide the current screen", TL_SUCCESS); 
			terminal->addLine("screen show : show the current screen", TL_SUCCESS); 
			terminal->addLine("quit : exit game", TL_SUCCESS); 
			terminal->addLine("exit : exit game", TL_SUCCESS); 
			terminal->addLine("screen main : go to main menu screen", TL_SUCCESS); 
			terminal->addLine("screen store : go to store screen", TL_SUCCESS); 
			terminal->addLine("screen settings : go to settings screen", TL_SUCCESS); 
			terminal->addLine("screen game : resume game", TL_SUCCESS); 
			terminal->addLine("screen newgame : make new game screen", TL_SUCCESS); 
			terminal->addLine("screen levelselect : go to level select screen", TL_SUCCESS); 
			terminal->addLine("delete savedata : delete savedata file and set to default values", TL_SUCCESS); 
			terminal->addLine("delete settings : delete settings and set to default values", TL_SUCCESS); 
			terminal->addLine("screensize [width] [height] : reset width and height of the screen", TL_SUCCESS); 
			terminal->addLine("fullscreen [on / off] : toggle fullscreen", TL_SUCCESS); 
			terminal->addLine("tutorial [on / off] : toggle tutorial", TL_SUCCESS); 
		}
		else if (args == "2"){
			terminal->addLine("-- The following commands are for the level editor --", TL_SUCCESS); 
			terminal->addLine("saveFile [file].[x].[y].[difficulty].[levelrequirement] : save current level to file with sent args", TL_SUCCESS); 
			terminal->addLine("save [file] : save current level to file", TL_SUCCESS); 
			terminal->addLine("editor open : open level editor", TL_SUCCESS); 
			terminal->addLine("editor close : close level editor", TL_SUCCESS); 
			terminal->addLine("scenery add tree : add new tree to level", TL_SUCCESS); 
			terminal->addLine("scenery add sign [text] : add new sign to level ", TL_SUCCESS); 
			terminal->addLine("scenery add hayBale : add new hay bale to level", TL_SUCCESS); 
			terminal->addLine("scenery add crate : add new crate", TL_SUCCESS); 
			terminal->addLine("scenery add fence : add new fence", TL_SUCCESS); 
			terminal->addLine("scenery add longCrate : add new long crate", TL_SUCCESS); 
			terminal->addLine("scenery add tallCrate : add new tall crate", TL_SUCCESS); 
			terminal->addLine("scenery add barn : add new barn", TL_SUCCESS); 
			terminal->addLine("scenery add houseBrown : add new brown house", TL_SUCCESS); 
			terminal->addLine("scenery add houseBlue : add new blue house", TL_SUCCESS); 
			terminal->addLine("scenery add barracks : add new barracks", TL_SUCCESS); 
			terminal->addLine("npc add soldier : add new soldier npc to level", TL_SUCCESS); 
			terminal->addLine("npc add sniper : add new sniper npc to level", TL_SUCCESS); 
			terminal->addLine("npc add cow : add new cow npc to level", TL_SUCCESS); 
			terminal->addLine("npc add hsoldier : add new heavy soldier npc to level", TL_SUCCESS); 
		}
		else if (args == "3"){
			terminal->addLine("npc add tank : add new tank npc to level", TL_SUCCESS); 
			terminal->addLine("npc add turret : add new turret npc to level", TL_SUCCESS); 
			terminal->addLine("npc add sam : add new sam site npc to level", TL_SUCCESS); 
			terminal->addLine("npc add civilian : add new civilian to level", TL_SUCCESS); 
			terminal->addLine("", TL_SUCCESS); 
			terminal->addLine("-- The following commands are for levels --", TL_SUCCESS); 
			terminal->addLine("level reset : reset the current level", TL_SUCCESS); 
			terminal->addLine("zoom default : sets the zoom to 1.0", TL_SUCCESS); 
			terminal->addLine("zoom [double] : set the level zoom to the sent value", TL_SUCCESS); 
			terminal->addLine("damage ufo [damage] : damage ufo by amount sent", TL_SUCCESS); 
			terminal->addLine("damage player [damage] : damage player by amount sent", TL_SUCCESS); 
			terminal->addLine("invincible : player takes no further damage", TL_SUCCESS); 
			terminal->addLine("nodamage : player takes no further damage", TL_SUCCESS); 
			terminal->addLine("mortal : player can start taking damage", TL_SUCCESS); 
			terminal->addLine("time [0-24] : set time of day to the sent value", TL_SUCCESS); 
			terminal->addLine("timeSpeed [value] : set how fast the time of day progresses", TL_SUCCESS); 
			terminal->addLine("tutorial skip : skip tutorial if in it", TL_SUCCESS); 
			terminal->addLine("", TL_SUCCESS); 
			terminal->addLine("-- The following commands are for level select --", TL_SUCCESS); 
			terminal->addLine("unlockall : unlocks all levels", TL_SUCCESS); 
		}
		
		return;
	}
	// Check for version command 
	else if (command == "version"){
		string version = string("version: ");
		version += toString(VERSION);
		terminal->addLine(version, TL_SUCCESS); 

		return;
	}
	// Close game
	else if (command == "exit" || command == "quit"){
		running = false;
	}
	// Delete savedata and settings file 
	else if (command == "delete"){
		if (args == "savedata"){
			// Delete file 
			remove("savedata");
			// Set save data to default 
			delete savedata;
			savedata = new SaveData();
			// Print line 
			terminal->addLine(line, TL_SUCCESS);
			return;
		}
		else if (args == "settings"){
			// Delete file 
			remove("settings");
			// Set settings to default 
			delete settings;
			settings = new Settings();
			// Print line 
			terminal->addLine(line, TL_SUCCESS);
			return;
		}

		terminal->addLine(line, TL_WARNING);
		return;
	}
	// Change screen size 
	else if (command == "screensize"){
		UITerminal::getCommandAndArgs(&args, &command, &args);
		
		int x = toInt(command);
		int y = toInt(args);

		if (x > 0 && y > 0){
			settings->setScreenWidth(x);
			settings->setScreenHeight(y);

			terminal->addLine(line, TL_SUCCESS);
			return;
		}

		terminal->addLine(line, TL_WARNING);
		return;
	}
	// Set fullscreen option
	else if (command == "fullscreen"){
		if (args == "on")
		{
			settings->setFullscreen(true);
			terminal->addLine(line, TL_SUCCESS);
			return;
		}
		else if (args == "off")
		{
			settings->setFullscreen(false);
			terminal->addLine(line, TL_SUCCESS);
			return;
		}

		terminal->addLine(line, TL_WARNING);
		return;
	}
	// Unlock all guns
	else if (command == "unlockAllGuns" || command == "unlockallguns"){
		savedata->unlockAllWeapons();
		terminal->addLine(line, TL_SUCCESS);
		return;
	}
	// Toggle tutorial 
	else if (command == "tutorial"){
		if (args == "on"){
			savedata->setShowTut(true);
			terminal->addLine(line, TL_SUCCESS);
			return;
		}
		else if (args == "off"){
			savedata->setShowTut(false);
			terminal->addLine(line, TL_SUCCESS);
			return;
		}
		else if (args == "skip"){
			// Do nothing (game screen checks this)
		}
		else {
			terminal->addLine(line, TL_WARNING);
			return;
		}
	}

	// Send command to screen 
	if (screen->parseCommand(terminal, command, args)) 
		return;
	
	terminal->addLine(line);
}

// Checks if the screen needs to be switched. 
void changeScreen(){
	if (screen == NULL) return;

	// Get transition code
	int tcode = screen->getTransitionCode();
	

	if (tcode != NO_TRANSITION){
		if (screen->getHideOnClose() && !screen->hidden())
			return;
		// Tell the screen there is no transition. 
		// This must be done after the hide on close check. 
		screen->setTransitionValue(NO_TRANSITION);

		switch (tcode){
		case NO_TRANSITION: 
			break;
		case SCREEN_LOAD:
			break;
		case SCREEN_QUIT:
			running = false;
			break;
		case RESTART_GAME:
			restart = true;
			running = false;
			break;
		case SCREEN_MAIN:
		case SCREEN_MAIN_SAVE_GAME:
		case SCREEN_STORE:
		case SCREEN_SETTINGS:
		case SCREEN_GAME_NEW:
		case SCREEN_GAME_RESUME:
		case SCREEN_EQUIP:
		case SCREEN_CREDITS:
		case SCREEN_LEVEL_SELECT:
		case SCREEN_FROM_FILE:

			// Delete screen if it is not game screen 
			if (tcode != SCREEN_MAIN_SAVE_GAME){
				// Tell screen to unload 
				screen_unload = screen;
				screen = NULL;
			}
			// Save game screen 
			else {
				gscreen = (GameScreen*)screen;
				screen = NULL;
			}

			// Set new screen 
			if (tcode == SCREEN_MAIN || 
				tcode == SCREEN_MAIN_SAVE_GAME)	screen = (UIScreen*)new MainScreen(gscreen != NULL);
			else if (tcode == SCREEN_STORE)		screen = (UIScreen*)new StoreScreen(savedata);
			else if (tcode == SCREEN_SETTINGS)	screen = (UIScreen*)new SettingsScreen(settings, savedata);
			else if (tcode == SCREEN_EQUIP)		screen = (UIScreen*)new EquipScreen(savedata);
			else if (tcode == SCREEN_CREDITS)	screen = (UIScreen*)new CreditsScreen();
			else if (tcode == SCREEN_LEVEL_SELECT) screen = (UIScreen*)new LevelSelectScreen(savedata);
			else if (tcode == SCREEN_FROM_FILE)
			{
				screen = (UIScreen*)new GameScreen(savedata);
				gscreen_unload = gscreen;
				gscreen = NULL;
			}
			else if (tcode == SCREEN_GAME_NEW) {
				screen = (UIScreen*)new GameScreen(savedata);
				gscreen_unload = gscreen;
				gscreen = NULL;
			}

			if (screen != NULL)
				screen->init((float)settings->getScreenWidth(),(float)settings->getScreenHeight(), soundHandler);

			// Resume game screen 
			if (tcode == SCREEN_GAME_RESUME) {
				if (gscreen != NULL){
					screen = gscreen;
					gscreen = NULL;
				}
				else {
					screen = (UIScreen*)new GameScreen(savedata);
					screen->init((float)settings->getScreenWidth(),(float)settings->getScreenHeight(), soundHandler);
				}
			}

			break;
		default:
			break;
		}
	}
}
 
/*
* Render game to screen 
*/
void onDraw()
{
	// Clear screen
	glClearColor(0.137f, 0.137f, 0.137f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw Screen
	if (screen != NULL) {
		screen->draw(&mgl, (TextureAtlas*)mUIAtlas);
		screen->drawFocus(&mgl, (TextureAtlas*)mUIAtlas);
	}

	// Draw terminal if not hidden 
	if (!terminal->hidden()){
		mgl.setProjectionMatrix(mgl.orthoMatrix);
		mUIAtlas->bindBuffers(&mgl);
		mUIAtlas->bindTexture(&mgl);
		terminal->draw(&mgl, mUIAtlas);
	}

	// Delete gamescreen if needed 
	if (gscreen_unload != NULL)
	{
		gscreen_unload->unload();
		delete gscreen_unload;
		gscreen_unload = NULL;
	}

	// Unload screen if needed
	if (screen_unload != NULL){
		cout << "Screen Unloading...\n";
		screen_unload->unload();
		// Delete old screen 
		delete screen_unload;
		screen_unload = NULL;
		cout << "Screen Unloaded\n";
	}
}
 
/** Game loop to update game state **/
int gameLoop(void *ptr){
	int beginTime; 		// the time when the cycle begun
	int timeDiff = 0; 	// the time it took for the cycle to execute
	int sleepTime; 		// ms to sleep ( < 0 if we're behind)
	int framesSkipped;  // number of frames being skipped
	sleepTime = 0;

	// Main update loop for the game 
	while(running){
		// Get the current system time in miliseconds 
		beginTime = SDL_GetTicks(); 

		// Update Game 
		onUpdate();

		// Draws Game
		if (!render)
			render = true;
					
		// calculate how long the cycle took in miliseconds 
		timeDiff = SDL_GetTicks() - beginTime;
		// calculate sleep time
		sleepTime = FRAME_PERIOD - timeDiff;
		// If sleepTime > 0 we're OK			
		if (sleepTime > 0)
			SDL_Delay(sleepTime);

		// Update if behind 
		framesSkipped = 0; // reset the frames skipped
		while (sleepTime < 0 && framesSkipped < MAX_FRAME_SKIPS){
			printf("Skipped Frame: \n");
			// We need to catch up, update without rendering
			onUpdate();
			sleepTime += FRAME_PERIOD;
			framesSkipped++;
		}
	}
	return 0;
}

/**
* Updates window events and renders screen. 
*/
void eventAndRenderLoop(){
	SDL_Event windowEvent;
	while (running)
	{
		// Check events 
        while( SDL_PollEvent( &windowEvent )){
			if (windowEvent.type == SDL_QUIT) running = false;

			if (windowEvent.type == SDL_WINDOWEVENT) {
				switch (windowEvent.window.event) {
				case SDL_WINDOWEVENT_SHOWN:
				case SDL_WINDOWEVENT_FOCUS_GAINED:
					WINDOW_VISIBLE = true;
					break;
				case SDL_WINDOWEVENT_HIDDEN:
				case SDL_WINDOWEVENT_MINIMIZED:
				case SDL_WINDOWEVENT_FOCUS_LOST:
					WINDOW_VISIBLE = false;
					break;
				case SDL_WINDOWEVENT_RESIZED:
					break;
				default:
					break;
				}
			}

			// Update IO handler 
			mKeyH.updateState(windowEvent);
			mMouseH.updateState(windowEvent);
        }

		// Render if requested 
		if (render && WINDOW_VISIBLE){
			// Call main drawing function 
			onDraw();
			
			// check OpenGL error
			GLenum err;
			while ((err = glGetError()) != GL_NO_ERROR) {
				cout << "OpenGL error: " << err << " - " << GLHandler::getGLErrorString(err) << "\n";
			}

			// Swap buffers 
			SDL_GL_SwapWindow(window);
			render = false;
		}
	}
}

int main(int argc, char* argv[])
{
	createGame();

	// Exit  
    exit(EXIT_SUCCESS);
}

// Game a new game 
void createGame(){
	// Load Data 
	settings = new Settings();
	loadSettings(settings);
	savedata = new SaveData();
	loadSaveData(savedata);
	
	// ======= Setup ======= //
	// Setup SDL
	SDL_Init(SDL_INIT_VIDEO); 
	// Get display settings 
	SDL_DisplayMode current;
    if(SDL_GetDesktopDisplayMode(0, &current) == 0)
        printf("Display #%d: current display mode is %dx%dpx @ %dhz. \n", 0, current.w, current.h, current.refresh_rate);
	else {
	    cout << "ERROR: " << SDL_GetError() << "\n";
		current.w = settings->getScreenWidth() + 100;
		current.h = settings->getScreenHeight() + 100;
	}

	// Create Window 
	if (settings->getFullscreen())
		window = SDL_CreateWindow("UFO Attack", 
			(int)(current.w * .5f - (settings->getScreenWidth() * .5f)), 
			(int)(current.h * .5f - (settings->getScreenHeight() * .5f)), 
			settings->getScreenWidth(),settings->getScreenHeight(), 
			SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
	else 
		window = SDL_CreateWindow("UFO Attack", 
			(int)(current.w * .5f - (settings->getScreenWidth() * .5f)), 
			(int)(current.h * .5f - (settings->getScreenHeight() * .5f)),  
			settings->getScreenWidth(),settings->getScreenHeight(), SDL_WINDOW_OPENGL);

	// Create the window context 
	SDL_GLContext context = SDL_GL_CreateContext(window);

	/// Set window icon 
	if (fexists("images/icon.bmp")){
		SDL_Surface* icon = SDL_LoadBMP("images/icon.bmp");
		// Remove icon background 
		SDL_SetColorKey(icon, SDL_TRUE, SDL_MapRGB(icon->format,0,0,0)); 
		SDL_SetWindowIcon(window,icon);
		// Free icon resources 
		if (icon) SDL_FreeSurface(icon);
	}

	// OpenGL Extension wrangler initialising  
	glewExperimental = GL_TRUE; 
	GLenum glew_status = glewInit();
	// Close if glew could not be set up 
	if (glew_status != GLEW_OK){
		fprintf(stderr, "Error Setting up GLEW: %s\n", glewGetErrorString(glew_status));
		exit(EXIT_FAILURE);
	}

	// GLEW Debug information
	cout << "Using GLEW Version: " << glewGetString(GLEW_VERSION) << "\n";
	if (GLEW_VERSION_4_0) cout << "Core extensions of OpenGL 1.1 to 4.0 are available.\n";
	else if (GLEW_VERSION_3_0) cout << "Core extensions of OpenGL 1.1 to 3.0 are available.\n";
	else if (GLEW_VERSION_2_1) cout << "Core extensions of OpenGL 1.1 to 2.1 are available.\n";
	else if (GLEW_VERSION_2_0) cout << "Core extensions of OpenGL 1.1 to 2.0 are available.\n";
	else if (GLEW_VERSION_1_5) cout << "Core extensions of OpenGL 1.1 to 1.5 are available.\n";
	// Opengl Debug Information
	cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
	cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
	cout << "GL Version: " << glGetString(GL_VERSION) << "\n";
	cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
	
	// Load resources 
	if (init_resources() == 1){
		// ======= Run ======= //

		// Create game loop thread 
		running = true;
		thread = SDL_CreateThread( gameLoop, "gameLoop", (void *)NULL);

		// Run Event and render loop 
		eventAndRenderLoop();
	}
	
	// ======= Exit ======= //

	// Free resoruces 
	free_resources();
	// Delete the window context
	SDL_GL_DeleteContext(context);
	// Destroy sdl window 
	SDL_DestroyWindow(window);

	// Unload SDL
	SDL_Quit();
	// Unload SDL sound
	Mix_CloseAudio();
	Mix_Quit();

	if (restart){
		restart = false;
		createGame();
	}
}
