#pragma once
/* Using the standard output for fprintf */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class GLHandler
{
	// Used to save memory 
	GLfloat color[4];
	
public:
	// Shader handles 
	GLuint program;
	GLint mPositionHandle;			// Position
	GLint mColorHandle;				// Color
	GLint mTextureHandle;			// Texture
	GLint mTextCordHandle;			// Texture UV's
	GLint mProjMatrixHandle;		// Projection Matrix
	GLint mModelMatrixHandle;		// Model Matrix 
	GLint mViewMatrixHandle;		// View Matrix 
	GLint mUseTextureHandle;		// Toggle to use textures 

	GLint mLightMap;				// Light Map
	GLint mUseLight;				// Toggle to use light
	GLint mResolution;				// Screen resolution

	// 2D lighting
	GLuint lightTextureId;			// Light texture ID
	GLuint lightFBOId;				// Light FBO id
	GLfloat lightClearColor[4];

	// Matrix's
	glm::mat4 orthoMatrix;
	glm::mat4 camera3DMatrix;

	// Screen Size
	float screen_width;
	float screen_height;

	// Functions
	GLHandler();
	~GLHandler();

	// Return screen width 
	float getScreenWidth();
	// Return screen height
	float getScreenHeight();

	// Call to load 
	int load(float screen_width, float screen_height);

	// Unload resources 
	void unload();

	// Call to set up gl for rendering
	void setupGL();

	// Call when done rendering 
	void endGL();

	// Set the gl flat color
	// This should be in the form of {R,G,B,A}
	void setFlatColor(const GLfloat* c);
	// Set the gl flat color with 4 floats 
	void setFlatColor(float r, float g, float b, float a);
	// Set the gl flat color with 3 floats from and array and one alpha.
	// c should be {r,g,b}
	void setFlatColor(const GLfloat* c, float a);
	
	// Set the Projection matrix for the shader. 
	// This is used to map the game to the screen, 
	// so use an orthographic matrix or a projection 
	// matrix.
	// use glm::mat4() for identity 
	void setProjectionMatrix(glm::mat4);
	
	// Set the View matrix for the shader. 
	// This is used as the camera for the game. 
	// use glm::mat4() for identity 
	void setViewMatrix(glm::mat4);

	// Set the model matrix for the shader. 
	// use glm::mat4() for identity 
	void setModelMatrix(glm::mat4);

	// Call to fix the ortho matrix if screen size has changed 
	void setOrthoMatrix(const float width,const float height);

	// Call to set resolution
	void setResolution(float width, float height);

	// Bind vertex and cord buffers
	void bindBuffers(GLfloat* verts, GLfloat* cords);
	// Bind texture 
	void bindTexture(int id);

	// Bind texture to specific index
	// index must be greater than 1 
	// 0 is used for general binding stuff
	// 1 is used for lighting 
	void bindTexture(int id, int index);

	// Switch the shader texture index 
	// Must have bound the texture to an index first.
	void useGLTexture(int index);

	// Set the 3d camera matrix settings 
	// Camera location  : glm::vec(0,0,0)
	// Target           : glm::vec(0,0,0)
	void setCamera3DMatrix(const glm::vec3 cameraLocation, const glm::vec3 targetLocation, const float aspectRatio);

	// Call to turn on and off textures
	void toggleTextures(bool);

	// Begin light rendering
	void lightBegin();
	// Begin light rendering with the given color
	void lightBegin(float r, float g, float b);

	// End light rendering
	void lightEnd();

	// Enable disable lights 
	void enableLight(bool value);

	// Get the string for the sent error 
	static std::string getGLErrorString(int error);
};