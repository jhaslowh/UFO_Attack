#include "LevelIO.h"

using namespace std;

// Save the sent level to the sent file
// Note: Just use file name, no extension or directory
void saveLevel(Handlers* handlers, std::string file, bool addToMaster){
	// Level pointers used during loading 
	LevelProperties* levelProps = (LevelProperties*)handlers->levelProps;
	Ground* ground = (Ground*)handlers->ground;
	SceneryHandler* sceneryHandler = (SceneryHandler*)handlers->sceneryHandler;
	NPCHandler* npcHandler = (NPCHandler*)handlers->npcHandler;


	size_t pos = 0;
	string storage[5];
	std::string delimiter = ".";
	int counter = 0;
	std::string line = file;
	while ((pos = line.find(delimiter)) != std::string::npos) 
	{
		storage[counter] = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());
		counter++;
	}
	storage[counter] = line;

	// Create file to save to 
	std::string fileLocation = "./Levels/";
	if (addToMaster)
		fileLocation.append(storage[0]);
	else 
		fileLocation.append(file);
	fileLocation.append(".txt");
	std::ofstream outfile (fileLocation.c_str());

	// Write file to file?
	outfile << "Location: " << fileLocation << " " << std::endl;
	outfile << "Level: " << file << " " << std::endl;
	//Requirements: 0
	//Difficulty: 1
	outfile << "Requirements: " << storage[4] << " " << std::endl;
	outfile << "Difficulty: " << storage[3] << " " << std::endl;

	// Write level properties 
	outfile << "PlayerX" << std::endl;
	outfile << levelProps->getPlayerSpawnX() << std::endl;
	outfile << "PlayerY" << std::endl;
	outfile << levelProps->getPlayerSpawnY() << std::endl;
	outfile << "LevelLeft" << std::endl;
	outfile << levelProps->getLevelLeft() << std::endl;
	outfile << "LevelRight" << std::endl;
	outfile << levelProps->getLevelRight() << std::endl;
	outfile << "LevelTop" << std::endl;
	outfile << levelProps->getLevelTop() << std::endl;
	outfile << "levelBottom" << std::endl;
	outfile << levelProps->getLevelBottom() << std::endl;

	// Write ground to file 
	outfile << " " << std::endl;
	outfile << "ground" << std::endl;
	outfile << "x y" << std::endl;
	outfile << ground->getType() << std::endl;
	for(int i = 0; i < ground->getPointCount(); i++){
		outfile << ground->getPoint(i)->getX() << ";" << ground->getPoint(i)->getY() << std::endl;
	}
	outfile << "end" << std::endl;

	// Write scenery to file 
	outfile << " " << std::endl;
	outfile << "scenery" << std::endl;
	outfile << "x y width height rotation scale imageid collides stopplayer type text" << std::endl;
	SceneryObject* headPoint = sceneryHandler->getHead();
	while (headPoint != NULL){
		if(headPoint->getType().compare("sign")!=0)
			outfile << headPoint->getX() << ";" << headPoint->getY() << ";" << headPoint->getWidth() << ";" << headPoint->getHeight() << ";" << headPoint->getRotation() << ";" << headPoint->getScale() << ";" << headPoint->getImageID() << ";" << headPoint->getCollides() << ";" << headPoint->getStopPlayer() << ";" << headPoint->getType() << ";" << std::endl;
		headPoint = headPoint->getNext();
	}
	headPoint = sceneryHandler->getHead();
	outfile << "end" << std::endl;
	outfile << "signs" << std::endl;
	outfile << "x y width height rotation scale imageid collides stopplayer type text" << std::endl;
	while (headPoint != NULL){
		if(headPoint->getType().compare("sign")==0)
			outfile << headPoint->getX() << ";" << headPoint->getY() << ";" << headPoint->getWidth() << ";" << headPoint->getHeight() << ";" << headPoint->getRotation() << ";" << headPoint->getScale() << ";" << headPoint->getImageID() << ";" << headPoint->getCollides() << ";" << headPoint->getStopPlayer() << ";" << headPoint->getType() << ";" << ((Sign*)headPoint)->getText() << std::endl;
		headPoint = headPoint->getNext();
	}
	outfile << "end" << std::endl;
	outfile << " " << std::endl;
			
	// Write npc's to file 
	outfile << "npcs" << std::endl;
	outfile << "x y type" << std::endl;
	NPC* npcItr = npcHandler->getHead();
	while (npcItr != NULL){
		outfile << npcItr->getSpawnX() << ";" << npcItr->getSpawnY() << ";" << npcItr->getSType() << std::endl;
		npcItr = npcItr->next;
	}
	outfile << "end" << std::endl;

	// Close output file 
	outfile.close();

	if (addToMaster){
		// Read in master level file to add new level to it
		int numberOfLevels = 0;
		//line;
		std::vector<std::string> data;
		ifstream myfile ("./Levels/MasterLevelFile.txt");
		if(myfile.is_open())
		{
			getline(myfile, line);
			numberOfLevels = atoi(line.c_str());
			std::string fileChecker;
			bool findRedudancy = false;
			for(int i=0;i<numberOfLevels;i++)
			{
				getline(myfile, line);
				data.push_back(line);
				fileChecker = line.substr(0, line.find("."));
				if(fileChecker.compare(file.substr(0, line.find("."))) == 0)
					findRedudancy = true;
			}
			if(!findRedudancy)
			{
				data.push_back(file);
				numberOfLevels++;
			}
			myfile.close();
		}
		else{
			std::cout << "ERROR: Could not find master level file\n";
		}

		// Write levels back to master file 
		std::ofstream newOutfile ("./Levels/MasterLevelFile.txt");
		if(newOutfile.is_open())
		{
			newOutfile << numberOfLevels << std::endl;
			for(int i=0;i<numberOfLevels;i++)
			{
				newOutfile << data[i] << std::endl;
			}
			newOutfile.close();
		}
	}
}

// Load the level from the sent file into the sent level pointer
// Note: Just use file name, no extension or directory
void loadLevel(Handlers* handlers, std::string file){
	bool debug = false;
	string line;

	// Append and insert data to get full file location
	file.append(".txt");
	file.insert(0, "./Levels/");
	
	// Make input file stream 
	ifstream myfile(file.c_str());

	// Try and open file 
	if(myfile.is_open())
	{
		// Level pointers used during loading 
		LevelProperties* levelProps = (LevelProperties*)handlers->levelProps;
		Player* player = (Player*)handlers->player;
		Ground* ground = (Ground*)handlers->ground;
		SceneryHandler* sceneryHandler = (SceneryHandler*)handlers->sceneryHandler;
		NPCHandler* npcHandler = (NPCHandler*)handlers->npcHandler;

		cout << "Loading level from file: \n" << file << "\n";
		getline(myfile, line);
		getline(myfile, line);

		while(!myfile.eof())
		{
			getline(myfile, line);
			if(line.compare("PlayerX")==0){
				getline(myfile, line);
				float tempX = (float)atoi(line.c_str());
				getline(myfile, line);
				levelProps->setPlayerSpawn(tempX,(float)atoi(line.c_str()));
				player->ufo->setLocation(levelProps->getPlayerSpawnX(), levelProps->getPlayerSpawnY());
			}
			else if(line.compare("LevelLeft")==0){
				getline(myfile, line);
				levelProps->setLevelLeft((float)atoi(line.c_str()));
			}
			else if(line.compare("LevelRight")==0){
				getline(myfile, line);
				levelProps->setLevelRight((float)atoi(line.c_str()));
			}
			else if(line.compare("ground")==0)
			{
				getline(myfile, line);
				getline(myfile, line);
				ground->setType((int)atoi(line.c_str()));
				getline(myfile, line);
				while(line.compare("end")!=0)
				{
					if (debug) cout << "new ground point\n";
					size_t pos = 0;
					string storage[2];
					std::string delimiter = ";";
					int counter = 0;
					while ((pos = line.find(delimiter)) != std::string::npos) 
					{
						storage[counter] = line.substr(0, pos);
						line.erase(0, pos + delimiter.length());
						counter++;
					}
					storage[counter] = line;
					ground->add(new Point((float)atoi(storage[0].c_str()),(float)atoi(storage[1].c_str())));
					if (debug) cout << "X: " << (float)atoi(storage[0].c_str()) << " Y: " << (float)atoi(storage[1].c_str()) << " \n";
					getline(myfile, line);
				}
			}
			else if(line.compare("scenery")==0)
			{
				if (debug) cout << "enter scenery" << std::endl;

				getline(myfile, line);
				//x y width height rotation scale imageid collides stopplayer
				getline(myfile, line);

				while(line.compare("end")!=0)
				{
					//getline(myfile, line);
					if (debug) cout << "SceneryLine: " << line << std::endl;
					size_t pos = 0;
					string storage[11];
					std::string delimiter = ";";
					int counter = 0;
					while ((pos = line.find(delimiter)) != std::string::npos) 
					{
						storage[counter] = line.substr(0, pos);
						line.erase(0, pos + delimiter.length());
						counter++;
					}
					storage[counter] = line;

					sceneryHandler->add(storage[9],std::string(""),
						(float)atoi(storage[0].c_str()),(float)atoi(storage[1].c_str()));

					if (debug) cout << "looping" << std::endl;
					getline(myfile, line);
				}
			}
			else if(line.compare("signs")==0)
			{
				getline(myfile, line);
				//x y width height rotation scale imageid collides stopplayer
				getline(myfile, line);
				while(line.compare("end")!=0)
				{
					//getline(myfile, line);
					if (debug) cout << "StartLine: " << line << std::endl;
					size_t pos = 0;
					string storage[11];
					std::string delimiter = ";";
					int counter = 0;
					while ((pos = line.find(delimiter)) != std::string::npos) 
					{
						storage[counter] = line.substr(0, pos);
						line.erase(0, pos + delimiter.length());
						counter++;
					}
					if (debug) cout << "Line: " << line << std::endl;
					storage[counter] = line;

					sceneryHandler->add("sign",storage[10],
						(float)atoi(storage[0].c_str()),(float)atoi(storage[1].c_str()));
					
					getline(myfile, line);
				}
			}
			else if(line.compare("npcs")==0)
			{
				if (debug) std::cout << "parsing npcs\n";
				int npcCounter=0;
				getline(myfile, line);
				getline(myfile, line);
				while(line.compare("end")!=0)
				{
					size_t pos = 0;
					string storage[3];
					std::string delimiter = ";";
					int counter = 0;
					while ((pos = line.find(delimiter)) != std::string::npos) 
					{
						storage[counter] = line.substr(0, pos);
						line.erase(0, pos + delimiter.length());
						counter++;
					}
					storage[counter] = line;

					// Add npc to npc handler
					npcHandler->addByName(storage[2], (float)atoi(storage[0].c_str()),(float)atoi(storage[1].c_str()));

					npcCounter++;
					getline(myfile, line);
					if (debug) cout << "NPC Counter: " << npcCounter << std::endl;
				}
				levelProps->setEnemyCount(npcCounter);
			}
			levelProps->setLevelBottom(ground->getBottomMost());
			levelProps->setLevelTop(ground->getTopMost() - 500.0f);

		}
		myfile.close();
	}
	else 
		cout << "Level file (" << file << ") could not be opened\n";
}
