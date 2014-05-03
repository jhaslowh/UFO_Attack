#include "GLHandler.h"

GLHandler::GLHandler(){
	screen_width = 0.0f;
	screen_height = 0.0f;

	lightClearColor[0] = 0.0f;
	lightClearColor[1] = 0.0f;
	lightClearColor[2] = 0.0f;
	lightClearColor[3] = 0.0f;
}
GLHandler::~GLHandler(){
	glDeleteProgram(program);
}

// Return screen width 
float GLHandler::getScreenWidth(){return screen_width;}
// Return screen height
float GLHandler::getScreenHeight(){return screen_height;}

/**
* Setup the shaders used for rendering 
*/
int GLHandler::load(float screen_width, float screen_height){
	this->screen_width = screen_width;
	this->screen_height = screen_height;

	// ---------------
	// Compile shaders
	// ---------------

	// Make the opengl shaders 
	GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;
 
	// Vertex shader 
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	const char *vs_source = 
    "#version 110  \n"  // OpenGL 2.0
	"in vec4 position;        " // Position handle 
	"in vec2 aTexCoordinate;  " // Texture coord handle 
	"varying vec2 vTexCoordinate;    " // Texture coord handle that both shaders use 
	"uniform mat4 modelm;            " // Model Matrix handle
	"uniform mat4 viewm;             " // View Matrix handle
	"uniform mat4 projm;             " // Projection Matrix handle
	"void main() {                   "
	"  vTexCoordinate = aTexCoordinate; "
	"  gl_Position = projm * viewm * modelm * position;"
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
    "#version 120  \n"  // OpenGL 2.0
	"uniform sampler2D texture;   " // Texture handle 
	"uniform sampler2D lightmap;  " // Light texture
	"uniform vec4 color;           " // Color handle
	"uniform float useTexture;     " // Set to 1 to use texture 
	"uniform float useLight;       " // Set to 1 to use light 
	"varying vec2 vTexCoordinate;  " // Texture coord handle that both shaders use 
	"uniform vec2 resolution;      " // Sceen resolution
	// Values used for calculations
	"vec4 newColor;	"
	"vec2 lightCord; " 
	"vec4 light; "

	"void main() {                  "
	"  if (useTexture > 0.5f)       "
	"    gl_FragColor = color * texture2D(texture, vTexCoordinate);"
	"  else "
	"    gl_FragColor = color;"
	   // Apply lights 
	"  if (useLight > .5f){         "
		 // Get light color
	"    lightCord = (gl_FragCoord.xy / resolution.xy);   "
	"    light = texture2D(lightmap, lightCord);          "

	     // Apply Overlay blending 
	/*"    if (gl_FragColor.r < 0.5f)  "
	"      newColor.r = gl_FragColor.r * light.r * 2.0f;        "
	"    else"
	"      newColor.r = 1.0f - (2.0f * ((1.0f - gl_FragColor.r) * (1.0f - light.r)));"

	"    if (gl_FragColor.g < 0.5f)  "
	"      newColor.g = gl_FragColor.g * light.g * 2.0f;        "
	"    else"
	"      newColor.g = 1.0f - (2.0f * ((1.0f - gl_FragColor.g) * (1.0f - light.g)));"

	"    if (gl_FragColor.b < 0.5f)  "
	"      newColor.b = gl_FragColor.b * light.b * 2.0f;        "
	"    else"
	"      newColor.b = 1.0f - (2.0f * ((1.0f - gl_FragColor.b) * (1.0f - light.b)));"*/

	     // Apply Linear Light blending 
		 // R blend
	"    if (gl_FragColor.r > 0.5f)  "
	"      newColor.r = gl_FragColor.r + (2.0f * (light.r - 0.5f)); "
	"    else"
	"      newColor.r = gl_FragColor.r + (2.0f * light.r) - 1.0f; "
		 // G Blend
	"    if (gl_FragColor.g > 0.5f)  "
	"      newColor.g = gl_FragColor.g + (2.0f * (light.g - 0.5f)); "
	"    else"
	"      newColor.g = gl_FragColor.g + (2.0f * light.g) - 1.0f; "
		 // B blend
	"    if (gl_FragColor.b > 0.5f)  "
	"      newColor.b = gl_FragColor.b + (2.0f * (light.b - 0.5f)); "
	"    else"
	"      newColor.b = gl_FragColor.b + (2.0f * light.b) - 1.0f; "

	     // Apply color
	"    newColor.a = gl_FragColor.a;       "
	"    gl_FragColor = newColor;			"
	"  }  "
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
	// Give the vertex shader to our shader program
	glAttachShader(program, vs);
	// Give the fragment shader to out shader program 
	glAttachShader(program, fs);
	// Similar to the linker for a compiler. 
	// Initializes all values to 0 and defines 
	// a location for each uniform and attrubute. 
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if (!link_ok) {
		fprintf(stderr, "glLinkProgram:");
		return 0;
	}

	// ----------------------
	// Grab shader attributes
	// ----------------------

	// get handle to fragment shader's vColor member
	mColorHandle = glGetUniformLocation(program, "color");
	// get handle to shape's transformation matrix
	mModelMatrixHandle = glGetUniformLocation(program, "modelm");
	mProjMatrixHandle = glGetUniformLocation(program, "projm");
	mViewMatrixHandle = glGetUniformLocation(program, "viewm");
	// get handle to vertex shader's vPosition member
	mPositionHandle = glGetAttribLocation(program, "position");
	// Grab texture information
	mTextureHandle = glGetUniformLocation(program, "texture");
	mTextCordHandle = glGetAttribLocation(program, "aTexCoordinate");
	mUseTextureHandle = glGetUniformLocation(program, "useTexture");
	// Lights 
	mLightMap = glGetUniformLocation(program, "lightmap");
	mUseLight = glGetUniformLocation(program, "useLight");
	// Resolution
	mResolution = glGetUniformLocation(program, "resolution");

	// Error check 
	if (mColorHandle == -1){
		fprintf(stderr, "Error grabbing color shader handle: \n");
		return 0;
	}
	if (mProjMatrixHandle == -1){
		fprintf(stderr, "Error grabbing world matrix shader handle: \n");
		return 0;
	}
	if (mModelMatrixHandle == -1){
		fprintf(stderr, "Error grabbing model matrix shader handle: \n");
		return 0;
	}
	if (mViewMatrixHandle == -1){
		fprintf(stderr, "Error grabbing camera matrix shader handle: \n");
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
		return 0;
	}
	if (mLightMap == -1){
		std::cout << "Error grabbing mLightMap handle: \n";
		return 0;
	}
	if (mUseLight == -1){
		std::cout << "Error grabbing mUseLight handle: \n";
		return 0;
	}
	if (mResolution == -1){
		std::cout << "Error grabbing mResolution handle: \n";
		return 0;
	}

	// ---------------
	// Setup 2D lights
	// ---------------
	// Create a texture object for light
	glGenTextures(1, &lightTextureId);
	// Set the active texture unit to texture unit 1.
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, lightTextureId); 
	// Set filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Create Texture 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (GLsizei)screen_width, (GLsizei)screen_height, 0,
				 GL_RGBA, GL_UNSIGNED_BYTE, 0);
	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
	             

	// Create a framebuffer object 
	glGenFramebuffers(1, &lightFBOId);
	// Bind FBO
	glBindFramebuffer(GL_FRAMEBUFFER, lightFBOId);

	// attach the texture to FBO color attachment point
	glFramebufferTexture2D(GL_FRAMEBUFFER,        // 1. fbo target: GL_FRAMEBUFFER 
						   GL_COLOR_ATTACHMENT0,  // 2. attachment point
						   GL_TEXTURE_2D,         // 3. tex target: GL_TEXTURE_2D
						   lightTextureId,        // 4. tex ID
						   0);                    // 5. mipmap level: 0(base)

	// check FBO status
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(status != GL_FRAMEBUFFER_COMPLETE){
		std::cout << "Could not generate frame buffer\n";
		return 0;
	}

	// Switch back to window-system-provided Framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// Set the active texture unit to texture unit 0.
	glActiveTexture(GL_TEXTURE0);

	return 1;
}

// Unload resources 
void GLHandler::unload(){
	glDeleteTextures(1, &lightTextureId);
	glDeleteFramebuffers(1, &lightFBOId);
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
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
}

// Set the flat color of the face 
void GLHandler::setFlatColor(const GLfloat* mColor){
	glUniform4fv(mColorHandle, 1, mColor);
}
// Set the gl flat color with 4 floats 
void GLHandler::setFlatColor(float r, float g, float b, float a){
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;
	glUniform4fv(mColorHandle, 1, color);
}
// Set the gl flat color with 3 floats from and array and one alpha.
// c should be {r,g,b}
void GLHandler::setFlatColor(const GLfloat* c, float a){
	color[0] = c[0];
	color[1] = c[1];
	color[2] = c[2];
	color[3] = a;
	glUniform4fv(mColorHandle, 1, color);
}

// Set the Projection matrix for the shader. 
// use glm::mat4() for identity 
void GLHandler::setProjectionMatrix(glm::mat4 matrix){
	glUniformMatrix4fv(mProjMatrixHandle, 1, GL_FALSE, glm::value_ptr(matrix));
}

// Set the camera matrix for the shader 
void GLHandler::setViewMatrix(glm::mat4 matrix){
	glUniformMatrix4fv(mViewMatrixHandle, 1, GL_FALSE, glm::value_ptr(matrix));
}

// Set the model matrix for the shader 
void GLHandler::setModelMatrix(glm::mat4 matrix){
	glUniformMatrix4fv(mModelMatrixHandle, 1, GL_FALSE, glm::value_ptr(matrix));
}

// Call to fix the ortho matrix if screen size has changed 
void GLHandler::setOrthoMatrix(const float w,const float h){
	// left, width, height, top
	orthoMatrix = glm::ortho( 0.0f, w, h, 0.0f, 1.0f, -1.0f);
}

// Call to set resolution
void GLHandler::setResolution(float width, float height){
	// Setup resolution
	GLfloat res[2];
	res[0] = width;
	res[1] = height;
	glUniform2fv(mResolution, 1, res);
}

// Bind vertex and cord buffers
void GLHandler::bindBuffers(GLfloat* verts, GLfloat* cords){
	/// Set up vertex and coord buffers 
	glEnableVertexAttribArray(mPositionHandle);
	glVertexAttribPointer(mPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, verts );

	/// Bind texture
	glEnableVertexAttribArray(mTextCordHandle);
	glVertexAttribPointer(mTextCordHandle, 2,GL_FLOAT, GL_FALSE, 0, cords);
}
// Bind texture 
void GLHandler::bindTexture(int id){
	toggleTextures(true);
	// Set the active texture unit to texture unit 0.
	glActiveTexture(GL_TEXTURE0);
	// Bind the texture to this unit.
	glBindTexture(GL_TEXTURE_2D, id);
	// Tell the texture uniform sampler to use this texture in the shader by binding to texture unit 0.
	glUniform1i(mTextureHandle, 0);
}

// Bind texture to specific index
// index must be greater than 1 
// 0 is used for general binding stuff
// 1 is used for lighting 
void GLHandler::bindTexture(int id, int index){
	if (index < 2)
		return;

	toggleTextures(true);	
	// Set the active texture unit to texture unit index.
	glActiveTexture(GL_TEXTURE0 + index);
	// Bind the texture to this unit.
	glBindTexture(GL_TEXTURE_2D, id);
	// Tell the texture uniform sampler to use this texture 
	// in the shader by binding to texture unit index.
	glUniform1i(mTextureHandle, index);

	// Set the active texture unit to texture unit 0 to set back to default.
	glActiveTexture(GL_TEXTURE0);
}

// Switch the shader texture index 
void GLHandler::useGLTexture(int index){
	glUniform1i(mTextureHandle, index);
}

// Set the 3d camera matrix settings 
// Camera location  : glm::vec(0,0,0)
// Target           : glm::vec(0,0,0)
void GLHandler::setCamera3DMatrix(const glm::vec3 cameraLocation, const glm::vec3 targetLocation, const float aspectRatio)
{
	glm::mat4 Projection = glm::perspective(45.0f, aspectRatio, 0.1f, 10000.0f);
	glm::mat4 View       = glm::lookAt(
		cameraLocation,   // Camera location
		targetLocation,   // Target look at location 
		glm::vec3(0,-1,0)  // Camera Up
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


// Begin light rendering
void GLHandler::lightBegin(){
	// set rendering destination to FBO
	glBindFramebuffer(GL_FRAMEBUFFER, lightFBOId);
	// Clear to gray
	// This is the neutral color and will have no effect
	glClearColor(.5f,.5f,.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	lightClearColor[0] = 0.5f;
	lightClearColor[1] = 0.5f;
	lightClearColor[2] = 0.5f;
	lightClearColor[3] = 1.0f;
}

// Begin light rendering with the given color
void GLHandler::lightBegin(float r, float g, float b){
	// set rendering destination to FBO
	glBindFramebuffer(GL_FRAMEBUFFER, lightFBOId);
	// Clear to gray
	// This is the neutral color and will have no effect
	glClearColor(r,g,b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	lightClearColor[0] = r;
	lightClearColor[1] = g;
	lightClearColor[2] = b;
	lightClearColor[3] = 1.0f;
}

// End light rendering
void GLHandler::lightEnd(){
	// unbind FBO
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Set the active texture unit to texture unit 1.
	glActiveTexture(GL_TEXTURE1);
	// Bind the texture to this unit.
	glBindTexture(GL_TEXTURE_2D, lightTextureId);
	// Tell the texture uniform sampler to use this
	// texture in the shader by binding to texture unit 1.
	glUniform1i(mLightMap, 1);

	// Set the active texture unit to texture unit 0 to set back to default.
	glActiveTexture(GL_TEXTURE0);
}

// Enable disable lights 
void GLHandler::enableLight(bool value){
	if (value)
		glUniform1f(mUseLight, 1.0f);
	else 
		glUniform1f(mUseLight, 0.0f);
}

// Get the string for the sent error 
std::string GLHandler::getGLErrorString(int error){
	switch (error){
	case GL_INVALID_ENUM:
		return std::string("GL_INVALID_ENUM");
		break;
	case GL_INVALID_VALUE:
		return std::string("GL_INVALID_VALUE");
		break;
	case GL_INVALID_OPERATION:
		return std::string("GL_INVALID_OPERATION");
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		return std::string("GL_INVALID_FRAMEBUFFER_OPERATION");
		break;
	case GL_OUT_OF_MEMORY:
		return std::string("GL_OUT_OF_MEMORY");
		break;
	default:
		break;
	}

	return "INVALID ERROR NUM";
}
