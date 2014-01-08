#ifdef WIN32
// pragma to remove extra console window under windows
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif

/* Using the standard output for fprintf */
#include <stdio.h>
#include <stdlib.h>
/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <glew.h>
/* Using the GLUT library for the base windowing setup */
#include <glut.h>

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

	sprite.setup(64,64,"test.png");

	return 1;
}
 
/*
* Render game to screen 
*/
void onDisplay()
{
	printf("Render\n");

	// Setup gl states 
	mgl.setupGL();
	// Set the current matrix 
	mgl.setWorldMatrix(mgl.orthoMatrix);
	mgl.setModelMatrix(glm::mat4(1));
	/* Clear the background as white */
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	GLfloat color[] = {1.0f,1.0f,1.0f,1.0f};
	mgl.setFlatColor(color);

	sprite.draw(mgl);

	/* Display the result */
	glutSwapBuffers();
	mgl.endGL();
}
 
/**
* Called when finished to free resources 
*/
void free_resources()
{
	printf("Free Resources\n");
	glDeleteProgram(mgl.program);
}
 
int main(int argc, char* argv[])
{
	/* Glut-related initialising functions */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutCreateWindow("CS 426 Project");
 
	/* Extension wrangler initialising */
	// Tell glew to use modern methods 
	glewExperimental = GL_TRUE; 
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		return EXIT_FAILURE;
	}
 
	/* When all init functions run without errors,
	the program can initialise the resources */
	if (1 == init_resources())
	{
		/* We can display it if everything goes OK */
		glutDisplayFunc(onDisplay);
		glutMainLoop();
	}
 
	/* If the program exits in the usual way,
	free resources and exit with a success */
	free_resources();
	return EXIT_SUCCESS;
}
