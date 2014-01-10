#include "GLHandler.h"

GLHandler::GLHandler(){}
GLHandler::~GLHandler(void){}

/**
* Setup the shaders used for rendering 
*/
int GLHandler::setupShaders(){
	// Make the opengl shaders 
	GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;
 
	// Vertex shader 
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	const char *vs_source = 
#ifdef GL_ES_VERSION_2_0
    "#version 100  \n"  // OpenGL ES 2.0
#else
    "#version 120  \n"  // OpenGL 2.1
#endif
	"attribute vec4 position;        " // Position handle 
	"attribute vec2 aTexCoordinate; " // Texture coord handle 
	"varying vec2 vTexCoordinate;   " // Texture coord handle that both shaders use 
	"uniform mat4 modelm;            " // Model Matrix handle
	"uniform mat4 worldm;            " // World Matrix handle
	"void main() {                   "
	"  vTexCoordinate = aTexCoordinate; "
	"  gl_Position = worldm * modelm * position;"
	"}";
	glShaderSource(vs, 1, &vs_source, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
	if (0 == compile_ok){
		fprintf(stderr, "Error in vertex shader\n");
		return 0;
	}

	// Fragment shader 
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	const char *fs_source =
#ifdef GL_ES_VERSION_2_0
    "#version 100  \n"  // OpenGL ES 2.0
#else
    "#version 120  \n"  // OpenGL 2.1
#endif
	"uniform sampler2D texture;   " // Texture handle 
	"uniform vec4 color;           " // Color handle
	"uniform float useTexture;     " // Set to 1 to use texture 
	"varying vec2 vTexCoordinate;  " // Texture coord handle that both shaders use 
	"void main() {                  "
	"  if (useTexture > 0.5f)       "
	"    gl_FragColor = (color * texture2D(texture, vTexCoordinate));"
	"  else                         "
	"    gl_FragColor = color;"
	"}";
	glShaderSource(fs, 1, &fs_source, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
	if (!compile_ok) {
		fprintf(stderr, "Error in fragment shader\n");
		return 0;
	}

	// Make shader program
	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if (!link_ok) {
		fprintf(stderr, "glLinkProgram:");
		return 0;
	}


	/* Grab shader attributes */

	// get handle to fragment shader's vColor member
	mColorHandle = glGetUniformLocation(program, "color");
	// get handle to shape's transformation matrix
	mModelMatrixHandle = glGetUniformLocation(program, "modelm");
	mWorldMatrixHandle = glGetUniformLocation(program, "worldm");
	// get handle to vertex shader's vPosition member
	mPositionHandle = glGetAttribLocation(program, "position");
	mTextureHandle = glGetUniformLocation(program, "texture");
	mTextCordHandle = glGetAttribLocation(program, "aTexCoordinate");
	mUseTextureHandle = glGetUniformLocation(program, "useTexture");
	
	// Error check 
	if (mColorHandle == -1){
		fprintf(stderr, "Error grabbing color shader handle: \n");
		return 0;
	}
	if (mWorldMatrixHandle == -1){
		fprintf(stderr, "Error grabbing world matrix shader handle: \n");
		return 0;
	}
	if (mModelMatrixHandle == -1){
		fprintf(stderr, "Error grabbing model matrix shader handle: \n");
		return 0;
	}
	if (mPositionHandle == -1){
		fprintf(stderr, "Error grabbing position shader handle: \n");
		return 0;
	}
	if (mTextureHandle == -1){
		fprintf(stderr, "Error grabbing texture shader handle: \n");
		return 0;
	}
	if (mTextCordHandle == -1){
		fprintf(stderr, "Error grabbing texture cord shader handle: \n");
		return 0;
	}
	if (mUseTextureHandle == -1){
		fprintf(stderr, "Error grabbing useTexture handle: \n");
	}

	return 1;
}

// Setup gl calls for drawing 
void GLHandler::setupGL(){
	// Set the cull face 
	glEnable(GL_CULL_FACE);
	// Set which cull face to use 
	glCullFace(GL_BACK);

	// Setup alpha blending 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Disable all setup 
void GLHandler::endGL(){
	// Disable cull face
	glDisable(GL_CULL_FACE);
	// Disable blend
	glDisable(GL_BLEND);
}

// Set the flat color of the face 
void GLHandler::setFlatColor(const GLfloat* mColor){
	glUniform4fv(mColorHandle, 1, mColor);
}

// Set the model matrix for the shader 
void GLHandler::setModelMatrix(glm::mat4 matrix){
	glUniformMatrix4fv(mModelMatrixHandle, 1, GL_FALSE, glm::value_ptr(matrix));
}

// Set the world matrix for the shader 
void GLHandler::setWorldMatrix(glm::mat4 matrix){
	glUniformMatrix4fv(mWorldMatrixHandle, 1, GL_FALSE, glm::value_ptr(matrix));
}

// Call to fix the ortho matrix if screen size has changed 
void GLHandler::setOrthoMatrix(const float w,const float h){
	// left, width, height, top
	orthoMatrix = glm::ortho( 0.0f, w, h, 0.0f, 1.0f, -1.0f);
}

// Set the 3d camera matrix settings 
// Camera location  : glm::vec(0,0,0)
// Target           : glm::vec(0,0,0)
void GLHandler::setCamera3DMatrix(const glm::vec3 cameraLocation, const glm::vec3 targetLocation, const float aspectRatio)
{
	glm::mat4 Projection = glm::perspective(45.0f, aspectRatio, 0.1f, 1000.0f);
	glm::mat4 View       = glm::lookAt(
		cameraLocation,   // Camera location
		targetLocation,   // Target look at location 
		glm::vec3(0,1,0)  // Camera 
	);  
	camera3DMatrix = Projection * View;
}

// Call to turn on and off textures
void GLHandler::toggleTextures(bool value){
	if (value)
		glUniform1f(mUseTextureHandle, 1.0f);
	else 
		glUniform1f(mUseTextureHandle, 0.0f);
}