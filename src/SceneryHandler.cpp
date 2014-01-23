#include "SceneryHandler.h"


SceneryHandler::SceneryHandler()
{
	objects = new SceneryObject*[1];
	objects[0] = NULL;
	setCount(50);
}

SceneryHandler::SceneryHandler(int size)
{
	objects = new SceneryObject*[1];
	objects[0] = NULL;
	setCount(size);
}

SceneryHandler::~SceneryHandler()
{
	for (int i = 0; i < count; i++){
		delete objects[i];
		objects[i] = NULL;
	}
	delete[] objects;
}

// Set count. Set the number of scenerey objects
// This will delete all objects 
void SceneryHandler::setCount(int size){
	// Free memory 
	for (int i = 0; i < count; i++){
		delete objects[i];
		objects[i] = NULL;
	}
	delete[] objects;

	// Set count
	count = size;

	// Make objects 
	objects = new SceneryObject*[count];
	for (int i = 0; i < count; i++){
		objects[i] = NULL;
	}
}

// Get number of scenery objects 
int SceneryHandler::getCount(){
	return count;
}

// Set the sent index as the sent pointer
void SceneryHandler::set(int index, SceneryObject* obj){
	if (index < 0 || index >= count)
		std::cout << "Scenery index out of bounds. Sent index: " << index << ", Array Size: " << count << "\n";
	
	delete objects[index];
	objects[index] = obj;
}

// Get the scenery object list 
SceneryObject** SceneryHandler::getObjects(){return objects;}

// Update objects
void SceneryHandler::update(float deltaTime, Handlers* handlers){
	for (int i = 0; i < count; i++){
		if (objects[i] != NULL)
			objects[i]->update(deltaTime, handlers);
	}
}

// Draw objects
void SceneryHandler::draw(GLHandler* mgl, GameAtlas* mGame){
	for (int i = 0; i < count; i++){
		if (objects[i] != NULL)
			objects[i]->draw(mgl, mGame);
	}
}