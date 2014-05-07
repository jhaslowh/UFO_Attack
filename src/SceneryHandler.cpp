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

// Add by name
bool SceneryHandler::add(std::string name, std::string args, float x, float y){
	SceneryObject* obj = NULL;
	if (name.compare("tallCrate") == 0){
		obj = new TallCrate();
		obj->setLocation(x,y);
		add(obj);
		return true;
	}
	else if (name.compare("sign") == 0){
		obj = new Sign();
		obj->setLocation(x,y);
		((Sign*)obj)->setText(args);
		add(obj);
		return true;
	}
	else if (name.compare("longCrate") == 0){
		obj = new LongCrate();
		obj->setLocation(x,y);
		add(obj);
		return true;
	}
	else if (name.compare("hayBale") == 0){
		obj = new HayBale();
		obj->setLocation(x,y);
		add(obj);
		return true;
	}
	else if (name.compare("fence") == 0){
		obj = new Fence();
		obj->setLocation(x,y);
		add(obj);
		return true;
	}
	else if (name.compare("crate") == 0){
		obj = new Crate();
		obj->setLocation(x,y);
		add(obj);
		return true;
	}
	else if (name.compare("tree") == 0){
		obj = new Tree();
		obj->setLocation(x,y);
		add(obj);
		return true;
	}
	else if (name.compare("barn") == 0){
		obj = new Barn();
		obj->setLocation(x,y);
		add(obj);
		return true;
	}
	else if (name.compare("houseBrown") == 0){
		obj = new HouseBrown();
		obj->setLocation(x,y);
		add(obj);
		return true;
	}
	else if (name.compare("houseBlue") == 0){
		obj = new HouseBlue();
		obj->setLocation(x,y);
		add(obj);
		return true;
	}
	else if (name.compare("barracks") == 0){
		obj = new Barracks();
		obj->setLocation(x,y);
		add(obj);
		return true;
	}
	return false;
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
