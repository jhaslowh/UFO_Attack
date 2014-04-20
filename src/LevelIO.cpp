#include "LevelIO.h"

using namespace std;

// Save the sent level to the sent file
// Note: Just use file name, no extension or directory
void saveLevel(Handlers* handlers, std::string file){
	// Level pointers used during loading 
	LevelProperties* levelProps = (LevelProperties*)handlers->levelProps;
	Player* player = (Player*)handlers->player;
	Ground* ground = (Ground*)handlers->ground;
	SceneryHandler* sceneryHandler = (SceneryHandler*)handlers->sceneryHandler;
	NPCHandler* npcHandler = (NPCHandler*)handlers->npcHandler;

	// Create file to save to 
	std::string fileLocation = ".\\Levels\\";
	fileLocation.append(file);
	fileLocation.append(".txt");
	std::ofstream outfile (fileLocation.c_str());

	// Write file to file?
	outfile << "Location: " << fileLocation << " " << std::endl;
	outfile << "Level: " << file << " " << std::endl;

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
		outfile << npcItr->getX() << ";" << npcItr->getY() << ";" << npcItr->getSType() << std::endl;
		npcItr = npcItr->next;
	}
	outfile << "end" << std::endl;

	// Close output file 
	outfile.close();
}

// Load the level from the sent file into the sent level pointer
// Note: Just use file name, no extension or directory
void loadLevel(Handlers* handlers, std::string file){
	bool debug = false;
	string line;

	// Append and insert data to get full file location
	file.append(".txt");
	file.insert(0, ".\\Levels\\");
	
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
				SceneryObject* obj;
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
					if(storage[9].compare("tree")==0)
					{
						obj = (SceneryObject*)new Tree();
						obj->setLocation((float)atoi(storage[0].c_str()),(float)atoi(storage[1].c_str()));
						sceneryHandler->add(obj);
						if (debug) cout << "tree" << std::endl;
					}
					else if(storage[9].compare("fence")==0)
					{
						obj = (SceneryObject*)new Fence();
						obj->setLocation((float)atoi(storage[0].c_str()),(float)atoi(storage[1].c_str()));
						sceneryHandler->add(obj);
					}
					else if(storage[9].compare("crate")==0)
					{
						obj = (SceneryObject*)new Crate();
						obj->setLocation((float)atoi(storage[0].c_str()),(float)atoi(storage[1].c_str()));
						sceneryHandler->add(obj);
					}
					else if(storage[9].compare("longcrate")==0)
					{
						obj = (SceneryObject*)new LongCrate();
						obj->setLocation((float)atoi(storage[0].c_str()),(float)atoi(storage[1].c_str()));
						sceneryHandler->add(obj);
					}
					else if(storage[9].compare("tallcrate")==0)
					{
						obj = (SceneryObject*)new TallCrate();
						obj->setLocation((float)atoi(storage[0].c_str()),(float)atoi(storage[1].c_str()));
						sceneryHandler->add(obj);
					}
					else if(storage[9].compare("hayBale")==0)
					{
						obj = (SceneryObject*)new HayBale();
						obj->setLocation((float)atoi(storage[0].c_str()),(float)atoi(storage[1].c_str()));
						sceneryHandler->add(obj);
					}
					if (debug) cout << "looping" << std::endl;
					getline(myfile, line);
				}
			}
			else if(line.compare("signs")==0)
			{
				getline(myfile, line);
				//x y width height rotation scale imageid collides stopplayer
				getline(myfile, line);
				SceneryObject* obj;
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
					//if((float)atoi(storage[0].c_str()))
					obj = (SceneryObject*)new Sign();
					((Sign*)obj)->setText(storage[10]);
					if (debug) cout << "Sign text: " << storage[10] << std::endl;
					obj->setLocation((float)atoi(storage[0].c_str()),(float)atoi(storage[1].c_str()));
					sceneryHandler->add(obj);
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
