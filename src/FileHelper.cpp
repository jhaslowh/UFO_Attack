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
	// String temporaries 
	std::string line;
	std::string str;
	std::string token;

	// Make a new file object 
	std::ifstream myfile ("settings");

	// Check if file can be opened 
	if (myfile.is_open())
	{
		// Read each line of the file and put it into a string 
		while ( getline (myfile,line) )
		{
			str += line + '\n';
		}
		// Close file 
		myfile.close();

		// Parse file 

		// Grab screen width 
		token = getSetting(str, std::string("screen_width"));
		s->setScreenWidth(toInt(token));

		// Grab screen height 
		token = getSetting(str, std::string("screen_height"));
		s->setScreenHeight(toInt(token));

		// Grab fullscreen
		token = getSetting(str, std::string("fullscreen"));
		int value = toInt(token);
		if (value == 1)
			s->setFullscreen(true);
		else 
			s->setFullscreen(false);

		std::cout << "Settings loaded\n";
	}
	else 
		std::cout <<  "Error opening settings file or file not created yet\n"; 
}

// Save the settings into settings file 
void saveSettings(Settings* s){
	// Create settings string 
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

	// Save 
	std::ofstream myfile("settings");
	if (myfile.is_open())
	{
		myfile << str;
		myfile.close();
	}
	else std::cout << "Unable to open settings file for writing\n";
}

// Convert int to string
std::string toString(int value){
	std::ostringstream buff;
    buff<<value;
    return buff.str();   
}

// Convert double to string
std::string toString(double value){
	std::ostringstream buff;
    buff<<value;
    return buff.str();   
}

// Convert string to int
int toInt(std::string s){
	int numb;
	std::istringstream (s) >> numb;
	return numb;
}

// Convert string to double
double toDouble(std::string s){
	double numb;
	std::istringstream (s) >> numb;
	return numb;
}

// Return setting from file 
std::string getSetting(std::string fileString, std::string setting){
	std::string token 
		  = fileString.substr(fileString.find(setting), fileString.length());
	token = token.substr(token.find(setting), token.find(std::string(";")));
	token = token.substr(token.find(std::string(" ")) + 1, token.length());
	return token;
}

