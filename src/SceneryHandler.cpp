#include "SceneryHandler.h"


SceneryHandler::SceneryHandler()
{
	head = NULL;
}

SceneryHandler::~SceneryHandler()
{
	while (head != NULL){
		itr = head;
		head = head->getNext();
		delete itr;
	}
}

// Get number of scenery objects 
int SceneryHandler::getSize(){
	itr = head;
	int count = 0;
	while (head != NULL){
		count++;
		head = head->getNext();
	}
	return count;
}

// Get head objective 
SceneryObject* SceneryHandler::getHead(){
	return head;
}
void SceneryHandler::setHead(SceneryObject* obj){
	head = obj;
}

// Add an scenery object to the list 
void SceneryHandler::add(SceneryObject* obj){
	// Check if list is empty
	if (head == NULL){
		head = obj;
		return;
	}
	
	itr = head;
	while (itr != NULL)
	{
		if (itr->getNext() == NULL){
			itr->setNext(obj);
			return;
		}
		itr = itr->getNext();
	}

	std::cout << "Error: counld not add item to scenery linked list\n";
}

// Update objects
void SceneryHandler::update(float deltaTime, Handlers* handlers){
	itr = head;
	while (itr != NULL){
		itr->update(deltaTime, handlers);
		itr = itr->getNext();
	}
}

// Draw objects
void SceneryHandler::draw(GLHandler* mgl, GameAtlas* mGame){
	itr = head;
	while (itr != NULL){
		itr->draw(mgl, mGame);
		itr = itr->getNext();
	}
}