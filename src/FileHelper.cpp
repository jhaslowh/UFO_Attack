#include "FileHelper.h"

int FileHelper::loadPNG(char* file){

	// Generate opengl textures
	GLuint textureHandle;
	glGenTextures(1, &textureHandle);

	// Load texture with soil 
	int width, height;
	unsigned char* image =
		SOIL_load_image(file, &width, &height, 0, SOIL_LOAD_RGB);

	// Bind to the texture in OpenGL
	glBindTexture(GL_TEXTURE_2D, textureHandle);
	// Load texture into bound texture 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
              GL_UNSIGNED_BYTE, image);
	             
	// Set filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Free image data
	SOIL_free_image_data(image);

	return textureHandle;
}