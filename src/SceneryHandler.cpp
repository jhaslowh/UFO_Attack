#include "SceneryHandler.h"


SceneryHandler::SceneryHandler()
{
	count = 1;
	objects = new SceneryObject*[1];
	objects[0] = NULL;
	setCount(10);
}

SceneryHandler::SceneryHandler(int size)
{
	count = 1;
	objects = new SceneryObject*[1];
	objects[0] = NULL;
	setCount(size);
}

SceneryHandler::~SceneryHandler()
{
	for (int i = 0; i < count; i++)
		delete objects[i];
	delete[] objects;

}

// Set count. Set the number of scenerey objects
// This will delete all objects 
void SceneryHandler::setCount(int size){
	// Free memory 
	for (int i = 0; i < count; i++)
		delete objects[i];
	delete[] objects;

	// Set count
	count = size;

	// Make objects 
	objects = new SceneryObject*[count];
	for (int i = 0; i < count; i ++)
		objects[i] = new SceneryObject();
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
		objects[i]->update(deltaTime, handlers);
	}
}

// Draw objects
void SceneryHandler::draw(GLHandler* mgl, GameAtlas* mGame){
	for (int i = 0; i < count; i++){
		objects[i]->draw(mgl, mGame);
	}
}