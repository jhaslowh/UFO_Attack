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
	
	// Set the active texture unit to texture unit 0.
	// Other units are used for different things. 0 is default, so 
	// we use that for general actions. 
	glActiveTexture(GL_TEXTURE0);
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

	// Unload texture
	glBindTexture(GL_TEXTURE_2D, 0);

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
		if(token != "null") s->setScreenWidth(toInt(token));

		// Grab screen height 
		token = getSetting(str, std::string("screen_height"));
		if(token != "null") s->setScreenHeight(toInt(token));

		// Grab fullscreen
		token = getSetting(str, std::string("fullscreen"));
		if(token != "null") {
			int value = toInt(token);
			if (value == 1)
				s->setFullscreen(true);
			else 
				s->setFullscreen(false);
		}

		// Grab master volume 
		token = getSetting(str, std::string("master_vol"));
		if(token != "null") s->setMasterVol((float)toDouble(token));

		// Grab music volume 
		token = getSetting(str, std::string("music_vol"));
		if(token != "null") s->setMusicVol((float)toDouble(token));

		// Grab sfx volume 
		token = getSetting(str, std::string("sfx_vol"));
		if(token != "null") s->setSfxVol((float)toDouble(token));

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

	// Master volume 
	str += "master_vol ";
	str += toString(s->getMasterVol());
	str += ";\n";

	// Music volume 
	str += "music_vol ";
	str += toString(s->getMusicVol());
	str += ";\n";

	// Sfx volume 
	str += "sfx_vol ";
	str += toString(s->getSfxVol());
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


// Load player save data 
void loadSaveData(SaveData* sd){
	// String temporaries 
	std::string line;
	std::string str;
	std::string token;

	// Make a new file object 
	std::ifstream myfile ("savedata");

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
		token = getSetting(str, std::string("store_items"));
		if(token != "null") {
			for (int i = 0; i < (int)token.length(); i++)
			{
				if (token[i] == '1')
					sd->itemPurchsed(i);
			}
		}

		// Grab human abduction count  
		token = getSetting(str, std::string("human_abduct"));
		if(token != "null") sd->setHumanAbductCount(toInt(token));

		// Grab animal abduction count
		token = getSetting(str, std::string("animal_abduct"));
		if(token != "null") sd->setAnimalAbductCount(toInt(token));

		// Load player starting weapons 
		token = getSetting(str, std::string("pw1"));
		if(token != "null") sd->setPlayerWeapon1(toInt(token));
		token = getSetting(str, std::string("pw2"));
		if(token != "null") sd->setPlayerWeapon2(toInt(token));

		// Load ufo starting weapons 
		token = getSetting(str, std::string("ufow1"));
		if(token != "null") sd->setUFOWeapon1(toInt(token));
		token = getSetting(str, std::string("ufow2"));
		if(token != "null") sd->setUFOWeapon2(toInt(token));

		// Grab level list 
		token = getSetting(str, std::string("clevels"));
		// Parse levels out of token 
		if (token != "null"){
			int spaceLoc = token.find(std::string(" "));
			while (spaceLoc != -1){
				sd->addLevel(token.substr(0, spaceLoc));
				token = token.substr(spaceLoc+1, token.length());
				spaceLoc = token.find(std::string(" "));
			}
			sd->addLevel(token);
		}

		// Grab tut shown
		token = getSetting(str, std::string("showtut"));
		if (token == "0")
			sd->setShowTut(false);

		std::cout << "Savedata loaded\n";
	}
	else 
		std::cout <<  "Error opening savedata file or file not created yet\n"; 
}

// Save player save data
void saveSaveData(SaveData* sd){
	// Create savedata string 
	std::string str("");

	// Store item bools 
	str += "store_items ";
	for (int i = 0; i < StoreItems::STORE_ITEM_COUNT; i++){
		if (sd->isItemPurchased(i))
			str += "1";
		else 
			str += "0";
	}
	str += ";\n";

	// Human abduct count 
	str += "human_abduct ";
	str += toString(sd->getHumanAbductCount());
	str += ";\n";

	// Animal abduct count 
	str += "animal_abduct ";
	str += toString(sd->getAnimalAbductCount());
	str += ";\n";

	// Player starting weapons 
	str += "pw1 ";
	str += toString(sd->getPlayerWeapon1());
	str += ";\n";
	str += "pw2 ";
	str += toString(sd->getPlayerWeapon2());
	str += ";\n";
	
	// UFO starting weapons 
	str += "ufow1 ";
	str += toString(sd->getUFOWeapon1());
	str += ";\n";
	str += "ufow2 ";
	str += toString(sd->getUFOWeapon2());
	str += ";\n";

	// Completed levels
	str += "clevels";
	str += sd->levelsToString();
	str += ";\n";

	// Tuts shown
	str += "showtut ";
	if (sd->getShowTut())
		str += "1;\n";
	else 
		str += "0;\n";

	// Save 
	std::ofstream myfile("savedata");
	if (myfile.is_open())
	{
		myfile << str;
		myfile.close();
	}
	else std::cout << "Unable to open savedata file for writing\n";
}

// ---------------------------------------- //
//       Helper Methods                     //
// ---------------------------------------- // 

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
// Returns "null" if invalid (not NULL)
std::string getSetting(std::string fileString, std::string setting){
	// Find location of setting 
	int front = fileString.find(setting);
	if (front == -1) return "null"; // Return null if no setting found

	// Grab the settings line to end of file 
	std::string token 
		  = fileString.substr(front, fileString.length());

	// Cut off end off settings line to end of file 
	front = token.find(setting);
	int end = token.find(std::string(";"));
	if (front == -1 || end == -1) return "null"; // Return null if either are invalid 
	token = token.substr(front, end);

	// Check if setting has anything after the name
	// If it doesn't, return null 
	if (token.compare(setting) == 0) return "null";

	// Cut off settings name 
	front = token.find(std::string(" ")) + 1;
	end = token.length();
	if (front == -1 || end == -1) return "null"; // Return null if either are invalid 
	token = token.substr(front, end);
	return token;
}

// Check if a file exists
bool fexists(const char *filename)
{
  std::ifstream ifile(filename);
  return ifile.is_open();
}
