#ifdef WIN32
// pragma to remove extra console window under windows
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
	// Set up shaders 
	mgl.setupShaders();
	glUseProgram(mgl.program);
	// Setup ortho matrix
	mgl.setOrthoMatrix((float)settings->getScreenWidth(),(float)settings->getScreenHeight());
	// Setup basic testing projection matrix 
	mgl.setCamera3DMatrix(glm::vec3(0,20,50), glm::vec3(0,0,0), 
		(float)settings->getScreenWidth()/(float)settings->getScreenHeight());
	// Set view matrix to identity to avoid rendering problems
	mgl.setViewMatrix(glm::mat4());

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

	// Set current screen as test screen 
	screen = (UIScreen*)new IntroLoadScreen();
	screen->init((float)settings->getScreenWidth(),(float)settings->getScreenHeight());

	printf("Resources loaded\n");
	return 1;
}

/**
* Called when finished to free resources 
*/
void free_resources()
{
	printf("Free Resources...\n");
	// Delete textures 
	screen->unload();
	mUIAtlas->unload();

	// Disable gl states 
	mgl.endGL();

	// Delete allocations 
	delete mUIAtlas;
	delete screen;
	delete terminal;

	// Save data 
	saveSettings(settings);
	delete settings;

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
		if (mKeyH.keyPressed(KEY_TILDE)){
			if (showTerminal){
				showTerminal = false;
				terminal->hide();
			}else {
				showTerminal = true;
				terminal->show();
			}
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
			if (!showTerminal) 
				screen->updateInput(&mKeyH, &mMouseH);
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
	string args("none");

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

		if (args != "none")
			terminal->addLine("Ignoring unrecognized arguments given to command: off", TL_WARNING);

		return;
	}
	// Check for restart command
	else if (command == "restart"){
		terminal->addLine(command, TL_SUCCESS);
		// Wait for rendering to stop 
		while (render){} 
		// Delete old screen 
		delete screen;
		// Switch to first screen 
		screen = (UIScreen*)new IntroLoadScreen();
		screen->init((float)settings->getScreenWidth(),(float)settings->getScreenHeight());

		if (args != "none"){
			terminal->addLine("Ignoring unrecognized arguments given to command: restart", TL_WARNING);
		}

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

		terminal->addLine("off: close terminal");
		terminal->addLine("restart: restart game");
		terminal->addLine("clear: clear terminal");
		terminal->addLine("version: prints out version");
		terminal->addLine("screen hide: hide screen");
		terminal->addLine("screen show: show screen");
		terminal->addLine("test: load test screen");
		terminal->addLine("exit: exit game");

		return;
	}
	// Check for version command 
	else if (command == "version"){
		string version = string("version: ");
		version += toString(VERSION);
		terminal->addLine(version, TL_SUCCESS); 

		return;
	}
	// Load test screen
	else if (command == "test"){
		// Wait for rendering to stop 
		while (render){} 
		// Delete old screen 
		delete screen;
		screen = (UIScreen*)new TestScreen();
		screen->init((float)settings->getScreenWidth(),(float)settings->getScreenHeight());
		terminal->addLine(command, TL_SUCCESS);
		return;
	}
	// Close game
	else if (command == "exit" || command == "quit"){
		running = false;
	}

	// Send command to screen 
	if (screen->parseCommand(terminal, command, args)) 
		return;
	
	terminal->addLine(line);
}

// Checks if the screen needs to be switched. 
void changeScreen(){
	if (screen == NULL) return;

	switch (screen->getTransitionCode()){
	case NO_TRANSITION: 
		break;
	case SCREEN_LOAD:
		break;
	case SCREEN_MAIN:
		unloadScreen = true;
		// Wait for rendering and unload to finish
		while (render || unloadScreen){} 
		// Delete old screen 
		delete screen;
		screen = (UIScreen*)new MainScreen();
		screen->init((float)settings->getScreenWidth(),(float)settings->getScreenHeight());
		break;
	case SCREEN_STORE:
		break;
	case SCREEN_SETTINGS:
		unloadScreen = true;
		// Wait for rendering and unload to finish
		while (render || unloadScreen){} 
		// Delete old screen 
		delete screen;
		screen = (UIScreen*)new SettingsScreen(settings);
		screen->init((float)settings->getScreenWidth(), (float)settings->getScreenHeight());
		break;
	case SCREEN_FREE_PLAY:
		unloadScreen = true;
		// Wait for rendering and unload to finish
		while (render || unloadScreen){} 
		// Delete old screen 
		delete screen;
		screen = (UIScreen*)new FreePlayScreen();
		screen->init((float)settings->getScreenWidth(), (float)settings->getScreenHeight());
		break;
	case SCREEN_GAME:
		unloadScreen = true;
		// Wait for rendering and unload to finish
		while (render || unloadScreen){} 
		// Delete old screen 
		delete screen;
		screen = (UIScreen*)new GameScreen();
		screen->init((float)settings->getScreenWidth(), (float)settings->getScreenHeight());
		break;
	case SCREEN_LEVEL_SELECT:
		break;
	case SCREEN_QUIT:
		running = false;
		break;
	case SCREEN_TEST:
		unloadScreen = true;
		// Wait for rendering and unload to finish
		while (render || unloadScreen){} 
		// Delete old screen 
		delete screen;
		screen = (UIScreen*)new TestScreen();
		screen->init((float)settings->getScreenWidth(),(float)settings->getScreenHeight());
		break;
	default:
		break;
	}
}
 
/*
* Render game to screen 
*/
void onDraw()
{
	// Clear screen
	glClearColor(0.25f, 0.25f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw Screen
	if (screen != NULL) {
		screen->draw(&mgl, (TextureAtlas*)mUIAtlas);

		// Draw terminal
		mgl.setProjectionMatrix(mgl.orthoMatrix);
		mUIAtlas->bindBuffers(&mgl);
		mUIAtlas->bindTexture(&mgl);

		terminal->draw(&mgl, mUIAtlas);
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
        while( SDL_PollEvent( &windowEvent ) ){
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
				printf("OpenGL error: %d\n", err);
			}

			// Swap buffers 
			SDL_GL_SwapWindow(window);
			render = false;
		}

		// Unload screen if needed
		if (unloadScreen){
			cout << "Screen Unloading...\n";
			screen->unload();
			unloadScreen = false;
			cout << "Screen Unloaded\n";
		}
	}
}

int main(int argc, char* argv[])
{
	// ======= Load Data ======= //
	settings = new Settings();
	loadSettings(settings);

	// ======= Setup ======= //
	// Setup SDL
	SDL_Init(SDL_INIT_VIDEO);
	// Create Window 
	if (settings->getFullscreen())
		window = SDL_CreateWindow("UFO Attack", 
			40, 40, settings->getScreenWidth(),settings->getScreenHeight(), SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
	else 
		window = SDL_CreateWindow("UFO Attack", 
			40, 40, settings->getScreenWidth(),settings->getScreenHeight(), SDL_WINDOW_OPENGL);
	// Create the window context 
	SDL_GLContext context = SDL_GL_CreateContext(window);

	/// Set window icon 
	SDL_Surface* icon = SDL_LoadBMP("icon.bmp");
	// Remove icon background 
	SDL_SetColorKey(icon, SDL_TRUE, SDL_MapRGB(icon->format,0,0,0)); 
	SDL_SetWindowIcon(window,icon);
	// Free icon resources 
	//SDL_FreeSurface(icon);

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
	init_resources();
	
	// ======= Run ======= //
	// Create game loop thread 

	thread = SDL_CreateThread( gameLoop, "gameLoop", (void *)NULL);

	// Run Event and render loop 
	eventAndRenderLoop();
	
	// ======= Exit ======= //
	// Free resoruces 
	free_resources();
	// Delete the window context
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	// Unload SDL
	SDL_Quit();
	// Exit  
    exit(EXIT_SUCCESS);
}
