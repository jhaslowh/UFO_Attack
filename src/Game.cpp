#ifdef WIN32
// pragma to remove extra console window under windows
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif

// Using the standard output for fprintf 
#include <stdio.h>
#include <stdlib.h>
// Use glew.h instead of gl.h to get all the GL prototypes declared 
#include <glew.h>
// Using the GLFW library for the base windowing setup 
#define GLFW_DLL
#include <GLFW\glfw3.h>
// Used to get system time 
#include <ctime>
// Used for sleep function
//#include <windows.h>
#define _AFXDLL
#include <afxwin.h>

#include "GLHandler.h"
#include "Game.h"
#include "Sprite.h"

// number of frames per second
int FPS = 60;
// maximum number of frames to be skipped
int MAX_FRAME_SKIPS = 12;
// the number of milliseconds per frame
int FRAME_PERIOD = 1000/FPS;
bool running = true;
bool render = false;
// Timing variables 
double lastTime = 0;
float deltaTime = 0;
SYSTEMTIME systime;
// GL handling class 
GLHandler mgl;
// Main window 
GLFWwindow* window;

// Testing sprite 
Sprite sprite;
float rotstat = 0;

/** Get the time diff of the two times in milliseconds.
This is used with the microsoft time functions because 
they return values between 0-1000, so new time could be
6 and old time could be 998. 
*/
double getTimeDiff(double oldt, double newt ){
	if (newt < oldt)
		return newt + (1000.0 - oldt);
	else if (oldt < newt)
		return newt - oldt;
	return 0;
}

/**
* Called at the begining of the game to load resources 
*/
int init_resources(void)
{
	printf("Load Resources\n");
	// Set up shaders 
	mgl.setupShaders();
	glUseProgram(mgl.program);

	sprite.setup(64.f,64.f,"test.png");
	sprite.setPosition(64.f,64.f);
	sprite.setRotation(45.0f);
	sprite.setScale(1.5f);
	sprite.setOrigin(32.0f,32.0f);
	sprite.setAlpha(.5f);

	return 1;
}

/**
* Called when finished to free resources 
*/
void free_resources()
{
	printf("Free Resources\n");
	glDeleteProgram(mgl.program);
}

/** 
 * Update game state 
 */
void onUpdate(){
	// Figure out delta time in seconds 
	if (lastTime != 0){
		// Get the system time in milliseconds 
		GetSystemTime(&systime);
		double mTime = systime.wMilliseconds;
		// Get the time since the last update 
		double diff = getTimeDiff(lastTime, mTime);
		deltaTime = (float)diff / 1000.0f;
		// Set this time as the last time 
		lastTime = mTime;
	}
	else {
		deltaTime = (float)FRAME_PERIOD / 1000.0f;
		// Set current time as the last time 
		GetSystemTime(&systime);
		lastTime = systime.wMilliseconds;
	}

	rotstat+=1.0f;
	sprite.setRotation(rotstat);
}
 
/*
* Render game to screen 
*/
void onDraw()
{
	// Setup gl states 
	mgl.setupGL();
	// Set the current matrix 
	mgl.setWorldMatrix(mgl.orthoMatrix);
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	sprite.draw(mgl);

	// Disable gl states 
	mgl.endGL();
}
 
/** Game loop to update game state **/
UINT gameLoop(LPVOID pParam){
	double beginTime; 	// the time when the cycle begun
	double timeDiff = 0; 	// the time it took for the cycle to execute
	int sleepTime; 	// ms to sleep (<0if we're behind)
	int framesSkipped;  // number of frames being skipped
	sleepTime = 0;

	while(running){
		GetSystemTime(&systime);
		beginTime = systime.wMilliseconds; // Get the current system time in miliseconds 
		framesSkipped = 0; // resetting the frames skipped
					
		// Update Game 
		onUpdate();
					
		// Draws Game
		if (!render)
			render = true;
		else 
			printf("Requested draw while drawing\n");
					
		// calculate how long the cycle took in miliseconds 
		GetSystemTime(&systime);
		timeDiff = getTimeDiff(beginTime,systime.wMilliseconds);
		// calculate sleep time
		sleepTime = FRAME_PERIOD - timeDiff;
		// If sleepTime > 0 we're OK			
		if (sleepTime > 0)
			Sleep(sleepTime);

		while (sleepTime < 0 && framesSkipped < MAX_FRAME_SKIPS){
			printf("Skipped Frame\n");
			// We need to catch up, update without rendering
			onUpdate();
			// add frame period to check if in next frame
			sleepTime += FRAME_PERIOD;
			framesSkipped++;
		}
		
		// Check if window was closed
		running = !glfwWindowShouldClose(window);
	}

	return 0;
}

// Error callback function 
static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

// Keyboard callback functon 
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check if escape key has been pressed 
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char* argv[])
{
	// Set error method 
    glfwSetErrorCallback(error_callback);
	// Initialize GLFW and exit if error 
    if (!glfwInit())
        exit(EXIT_FAILURE);
	// Make the GLFW Window 
    window = glfwCreateWindow(640, 480, "CS 426 Project", NULL, NULL);
	// If window could not be created, exit 
    if (!window){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
	// Set the GLFW context as this window 
    glfwMakeContextCurrent(window);
	// Set the keyboard callback 
    glfwSetKeyCallback(window, key_callback);
	
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
	
	// Run loop
	AfxBeginThread(gameLoop, NULL); 

	// Rendering loop 
	/* Updating and rendering are in separate threads because 
	 * otherwise rendering stops the main thread while it 
	 * renders. Mainly the glfwSwapBuffers() function. */
	while (running){
		if (render){
			onDraw();
			glfwSwapBuffers(window);
			
			// Must be called after each update to register other events 
			// This probably should not be in the rendering loop, 
			// but it needs to be in the main thread, and must be 
			// called alongside the gameloop
			glfwPollEvents();
			render = false;
		}
	}

	// Destoy window context 
    glfwDestroyWindow(window);
	// Free resoruces 
	free_resources();
	// Terminate GLFW
    glfwTerminate();
	// Exit app 
    exit(EXIT_SUCCESS);
}
