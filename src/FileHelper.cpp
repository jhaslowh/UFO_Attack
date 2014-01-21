#include "FileHelper.h"

// Load a texture into opengl 
int loadPNG(std::string file){
	// Generate opengl textures
	GLuint textureHandle;
	glGenTextures(1, &textureHandle);

	// Load texture with soil 
	int width, height;
	unsigned char* image =
		SOIL_load_image(file.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

	// Bind to the texture in OpenGL
	glBindTexture(GL_TEXTURE_2D, textureHandle);
	// Load texture into bound texture 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
              GL_UNSIGNED_BYTE, image);
	             
	// Set filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Free image data
	SOIL_free_image_data(image);

	return textureHandle;
}

// Load the settings into sent object
void loadSettings(Settings* s){
	// Open the settings file 
	SDL_RWops *rw = SDL_RWFromFile("settings","r");

	if (rw != NULL) {
		// Load file into string 
		char buf[1024];
		SDL_RWread(rw, buf, sizeof (buf), 1);
		string str(buf);
		SDL_RWclose(rw);

		// Parse file 
		std::string token;

		// Grab screen width 
		token = str.substr(str.find(string("screen_width")), str.find(string(";")));
		token = token.substr(token.find(string(" ")) + 1, token.length());
		s->setScreenWidth(toInt(token));

		// Grab screen height 
		token = str.substr(str.find(string("screen_height")), str.find(string(";")));
		token = token.substr(token.find(string(" ")) + 1, token.length());
		s->setScreenHeight(toInt(token));

		// Grab fullscreen
		token = str.substr(str.find(string("fullscreen")), str.find(string(";")));
		token = token.substr(token.find(string(" ")) + 1, token.length());
		int value = toInt(token);
		if (value == 1)
			s->setFullscreen(true);
		else 
			s->setFullscreen(false);

		cout << "Settings loaded\n";
	}
	else 
		cout << "Error opening settings file or file not created yet\n";
}

// Save the settings into settings file 
void saveSettings(Settings* s){

	// Create a new settings file
	// w+ : Create an empty file for both reading and writing. 
	//      If a file with the same name already exists its content is 
	//      erased and the file is treated as a new empty file.
	SDL_RWops *rw = SDL_RWFromFile("settings","w+");
	// Error if file could not be opened 
	if(rw == NULL) {
		cout << "Could not open settings file for writing\n";
		return;
	}

	// Write to file
	std::string str("");

	// Screen width 
	str += "screen_width ";
	str += toString(s->getScreenWidth());
	str += ";\n";

	// Screen height 
	str += "screen_height ";
	str += toString(s->getScreenHeight());
	str += ";\n";

	// Fullscreen
	str += "fullscreen ";
	if (s->getFullscreen())
		str += "1";
	else 
		str += "0";
	str += ";\n";

	const char* cstr = str.c_str();
	size_t size = sizeof(cstr);
	size_t len = SDL_strlen(cstr);

	// Write data to file 
	if (SDL_RWwrite(rw, cstr, size, len) != len)
		cout << "Error writing to settings file\n";
	else 
		cout << "Settings saved\n";
	
	// Close data file 
	SDL_RWclose(rw);
}

// Convert int to string
string toString(int value){
	ostringstream buff;
    buff<<value;
    return buff.str();   
}

// Convert string to int
int toInt(string s){
	int numb;
	istringstream (s) >> numb;
	return numb;
}