#ifdef WIN32
// pragma to remove extra console window under windows
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif

/* Using the standard output for fprintf */
#include <stdio.h>
#include <stdlib.h>
/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <glew.h>
/* Using the GLFW library for the base windowing setup */
#include <GLFW/glfw3.h>

#include "GLHandler.h"
#include "Game.h"
#include "Sprite.h"

// Our gl wrapping class 
GLHandler mgl;

// Testing sprite 
Sprite sprite;

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
float rotstat = 0;
void onUpdate(){
	// TODO 
	
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
	mgl.setModelMatrix(glm::mat4(1));
	/* Clear the background as white */
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	sprite.draw(mgl);

	// Disable gl states 
	mgl.endGL();
}
 
/** Game loop to update game state **/
void gameLoop(){

}

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char* argv[])
{
	GLFWwindow* window;
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

	// Set the GLFW context as this winow 
    glfwMakeContextCurrent(window);
	// Set the keyboard callback 
    glfwSetKeyCallback(window, key_callback);
	
	// Extension wrangler initialising  
	glewExperimental = GL_TRUE; 
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		return EXIT_FAILURE;
	}

	// Load resources 
	init_resources();
	
	// Window loop 
    while (!glfwWindowShouldClose(window))
	{
		onUpdate();
		onDraw();
        glfwSwapBuffers(window);
        glfwPollEvents();
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
