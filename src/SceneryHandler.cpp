#include "SceneryHandler.h"


SceneryHandler::SceneryHandler()
{
	head = NULL;
}

SceneryHandler::~SceneryHandler()
{
	SceneryObject* itr;
	while (head != NULL){
		itr = head;
		head = head->getNext();
		delete itr;
	}
}

// Get number of scenery objects 
int SceneryHandler::getSize(){
	SceneryObject* itr = head;
	int count = 0;
	while (itr != NULL){
		count++;
		itr = itr->getNext();
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
	
	SceneryObject* itr = head;
	while (itr != NULL)
	{
		if (itr->getNext() == NULL){
			itr->setNext(obj);
			return;
		}
		itr = itr->getNext();
	}

	std::cout << "Error: could not add item to scenery linked list\n";
}

// Update objects
void SceneryHandler::update(float deltaTime, Handlers* handlers){
	uitr = head;
	while (uitr != NULL){
		uitr->update(deltaTime, handlers);
		uitr = uitr->getNext();
	}
}

// Update objects input 
void SceneryHandler::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH, Handlers* handlers){
	uitr = head;
	while (uitr != NULL){
		uitr->updateInput(mKeyH, mMouseH, handlers);
		uitr = uitr->getNext();
	}
}

// Draw object lights 
void SceneryHandler::drawLight(GLHandler* mgl, GameAtlas* mGame){
	ditr = head;
	while (ditr != NULL){
		ditr->drawLight(mgl, mGame);
		ditr = ditr->getNext();
	}
}

// Draw objects
void SceneryHandler::draw(GLHandler* mgl, GameAtlas* mGame){
	ditr = head;
	while (ditr != NULL){
		ditr->draw(mgl, mGame);
		ditr = ditr->getNext();
	}
}

// Draw object ui elements 
void SceneryHandler::drawUI(GLHandler* mgl, UIAtlas* mUI){
	ditr = head;
	while (ditr != NULL){
		ditr->drawUI(mgl, mUI);
		ditr = ditr->getNext();
	}
}

