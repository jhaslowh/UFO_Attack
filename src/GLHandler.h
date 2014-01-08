#pragma once
/* Using the standard output for fprintf */
#include <stdio.h>
#include <stdlib.h>
#include <glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>


class GLHandler
{
public:
	// Shader handles 
	GLuint program;
	GLint mPositionHandle;
	GLint mColorHandle;
	GLint mTextureHandle;
	GLint mTextCordHandle;
	GLint mWorldMatrixHandle;
	GLint mModelMatrixHandle;

	// Matrix's
	glm::mat4 orthoMatrix;

	// Functions
	GLHandler();
	~GLHandler(void);
	// Call to load shaders 
	int setupShaders();

	// Call to set up gl for rendering
	void setupGL();
	// Call when done rendering 
	void endGL();
	// Set the gl flat color
	// This should be in the form of {R,G,B,A}
	void setFlatColor(const GLfloat*);

	void setModelMatrix(glm::mat4);
	void setWorldMatrix(glm::mat4);
};