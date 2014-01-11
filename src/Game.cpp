#ifdef WIN32
// pragma to remove extra console window under windows
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif

// Using the standard output for printf 
#include <stdio.h>
#include <stdlib.h>
// Use glew.h instead of gl.h to get all the GL prototypes declared 
#include <glew.h>
// Using the SDL library for the base windowing setup 
#include <SDL\SDL.h>
#include <SDL\SDL_opengl.h>
#include <SDL\SDL_thread.h>
#include <SDL\SDL_timer.h>

#include "GLHandler.h"
#include "TextRender.h"
#include "KeyHandler.h"
#include "Sprite.h"
#include "Cube.h"

// Global screen size references 
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;  

/** Game loop and FPS timing **/
int FPS = 60;				// number of frames per second
int MAX_FRAME_SKIPS = 12;	// maximum number of frames to be skipped
int FRAME_PERIOD = 1000/FPS;// the number of milliseconds per frame
int lastTime = 0;			
float deltaTime = 0;		// Used in game loop to tell how much time has passed

// States 
bool running = true;		
bool render = false;        // Set to true each time game needs to be rendered 

// Handlers
GLHandler mgl;
KeyHandler mKeyH;
TextRender* mTR;
// Main window 
SDL_Window* window;
SDL_Thread* thread;

// Testing sprite 
Sprite sprite;
float rotstat = 0;
Cube cube;

/**
* Called at the begining of the game to load resources 
*/
int init_resources(void)
{
	printf("Loading Resources...\n");
	// Set up shaders 
	mgl.setupShaders();
	glUseProgram(mgl.program);
	// Setup ortho matrix
	mgl.setOrthoMatrix((float)SCREEN_WIDTH,(float)SCREEN_HEIGHT);
	mgl.setCamera3DMatrix(glm::vec3(0,20,50), glm::vec3(0,0,0), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT);

	mTR = new TextRender();
	mTR->init();

	sprite.setup(64.f,64.f,"test2.png");
	sprite.setPosition(64.f,64.f);
	sprite.setScale(1.0f);
	sprite.setOrigin(32.0f,32.0f);
	sprite.setAlpha(1.0f);

	cube.setScale(5.0f);
	cube.setTexture("test.png");

	printf("Resources loaded\n");
	return 1;
}

/**
* Called when finished to free resources 
*/
void free_resources()
{
	printf("Free Resources\n");
	glDeleteProgram(mgl.program);
	delete(mTR);
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

	rotstat += 90.0f * deltaTime;
	sprite.setRotation(rotstat);

	if (mKeyH.keyDown(KEY_W))
		cube.setRotationX(cube.getRotationX() - 5.0f);
	if (mKeyH.keyDown(KEY_S))
		cube.setRotationX(cube.getRotationX() + 5.0f);
	if (mKeyH.keyDown(KEY_A))
		cube.setRotationY(cube.getRotationY() - 5.0f);
	if (mKeyH.keyDown(KEY_D))
		cube.setRotationY(cube.getRotationY() + 5.0f);
}
 
/*
* Render game to screen 
*/
void onDraw()
{
	// Setup gl states 
	mgl.setupGL();
	// Clear screen
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	mgl.setWorldMatrix(mgl.orthoMatrix);

	
	GLfloat color[] = {1.0f,0.0f,0.0f,1.0f};
	mgl.setFlatColor(color);
	mTR->drawText(mgl,
		"AaBbCcDdEeFf\n"
		"GgHhIiJjKkLlMm\n"
		"NnOoPpQqRrSs\n"
		"TtUuVvWwXxYyZz\n"
		"0123456789:.%-/?\n"
		,150,10,0,20);
	GLfloat color2[] = {.5,.5f,.5f,1.0f};
	mgl.setFlatColor(color2);
	mTR->drawText(mgl, 
		"This is an example sentence.",
		50,150,0,25);
	mTR->drawText(mgl, 
		"This is an example rotated sentence.",
		50,200,20,25);
	sprite.draw(mgl);

	mgl.setWorldMatrix(mgl.camera3DMatrix);
	cube.draw(mgl);

	// Disable gl states 
	mgl.endGL();
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
		
		// Behind 
		framesSkipped = 0; // resetting the frames skipped
		while (sleepTime < 0 && framesSkipped < MAX_FRAME_SKIPS){
			printf("Skipped Frame\n");
			// We need to catch up, update without rendering
			onUpdate();
			// add frame period to check if in next frame
			sleepTime += FRAME_PERIOD;
			framesSkipped++;
		}
	}

	return 0;
}

int main(int argc, char* argv[])
{
	// Setup SDL
	SDL_Init(SDL_INIT_VIDEO);
	// Create Window 
	window = SDL_CreateWindow("CS 426 Project", 
		100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	// Create the window context 
	SDL_GLContext context = SDL_GL_CreateContext(window);

	// Extension wrangler initialising  
	glewExperimental = GL_TRUE; 
	GLenum glew_status = glewInit();
	// Close if glew could not be set up 
	if (glew_status != GLEW_OK){
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
        exit(EXIT_FAILURE);
	}

	// Load resources 
	init_resources();

	// Create game loop thread 
	thread = SDL_CreateThread( gameLoop, "gameLoop", (void *)NULL);

	// Run UI and render loop 
	SDL_Event windowEvent;
	while (running)
	{
		// Check events 
        while( SDL_PollEvent( &windowEvent ) ){
                
			if (windowEvent.type == SDL_QUIT) running = false;
			if (windowEvent.type == SDL_KEYUP &&
				windowEvent.key.keysym.sym == SDLK_ESCAPE) running = false;

			// Update keyboard handler 
			mKeyH.updateState(windowEvent);
        }

		// Render if requested 
		if (render){
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
	}

	// Free resoruces 
	free_resources();
	// Delete the window context
	SDL_GL_DeleteContext(context);
	// Unload SDL
	SDL_Quit();
	// Exit app 
    exit(EXIT_SUCCESS);
}
