#include "LevelEditor.h"

LevelEditor::LevelEditor()
{
	shrinkSpeed = 5.0f;
	maxPointDistance = 6.0f;
	selectedPoint = NULL;
	pointHighlighted = false;
	enabled = false;
	sceneryOffsetX = 0;
	sceneryOffsetY = 0;
	scObj = NULL;

	levelX = 0.0f;
	levelY = 0.0f;

	state = LES_NONE;
	bMove = NULL;
	bAdd = NULL;
	bRemove = NULL;
	tTerminal = NULL;
}
LevelEditor::~LevelEditor(){
	delete bMove;
	delete bAdd;
	delete bRemove;
	delete tTerminal;
}

// Check if turned on
bool LevelEditor::Enabled(){
	return enabled;
}

// Setup basic structures
void LevelEditor::init(float screen_width, float screen_height){
	bMove = new UIButton(5,5,100.0f,35.0f, std::string("Move Obj"));
	bMove->setupHide(HT_HOROZONTAL,bMove->getX()-100.0f,.2f,true);
	bMove->setHidden();

	bAdd = new UIButton(5,45.0f,100.0f,35.0f, std::string("Add"));
	bAdd->setupHide(HT_HOROZONTAL,bAdd->getX()-100.0f,.2f,true);
	bAdd->setHidden();

	bRemove = new UIButton(5,85.0f,100.0f,35.0f, std::string("Remove"));
	bRemove->setupHide(HT_HOROZONTAL,bRemove->getX()-100.0f,.2f,true);
	bRemove->setHidden();

	bRemoveS = new UIButton(5,125.0f,100.0f,35.0f, std::string("Remove S"));
	bRemoveS->setupHide(HT_HOROZONTAL,bRemoveS->getX()-100.0f,.2f,true);
	bRemoveS->setHidden();

	tTerminal = new UITerminal();
	tTerminal->setLocation(5.0f,screen_height - 35.0f);
	tTerminal->setSize(450.0f,0.0f);
	tTerminal->setupHide(HT_VERTICAL,tTerminal->getY()+100.0f,.2f,false);
	tTerminal->setHidden();
}

// Load editor 
void LevelEditor::load(TextureAtlas* mAtlas){
	pointSprite.setup(8.0f,8.0f,"images/point.png");
	pointSprite.setOrigin(4.0f,4.0f);
	pointSprite.setColor(.8f,.8f,1.0f,1.0f);
	pointSprite.setScale(0.0f);
	
	UIAtlas* mUI = (UIAtlas*)mAtlas;
	bMove->centerText(mUI->mTextRender);
	bAdd->centerText(mUI->mTextRender);
	bRemove->centerText(mUI->mTextRender);
	bRemoveS->centerText(mUI->mTextRender);
}

// Update editor state 
void LevelEditor::update(float deltaTime, Handlers* handlers){
	// Shrink point sprite if point not selected
	if (!pointHighlighted){
		if (pointSprite.getScale() > 0.0f){
			pointSprite.setScale(pointSprite.getScale() - (shrinkSpeed * deltaTime));
			if (pointSprite.getScale() < 0.0f)
				pointSprite.setScale(0.0f);
		}
	}
	// Grow sprite if point is selected 
	else {
		// Grow sprite 
		if (pointSprite.getScale() < 1.25f){
			pointSprite.setScale(pointSprite.getScale() + (shrinkSpeed * deltaTime));
			if (pointSprite.getScale() > 1.25f)
				pointSprite.setScale(1.25f);
		}
	}

	// Update button 
	bMove->update(deltaTime);
	bAdd->update(deltaTime);
	bRemove->update(deltaTime);
	bRemoveS->update(deltaTime);
	tTerminal->update(deltaTime);

	// Update State string 
	if (state == LES_NONE || state == LES_MOVE_POINT || state == LES_SCENERY){
		stateString.clear();
		stateString += "State: Move Object";
	}
	else if (state == LES_ADD_POINT){
		stateString.clear();
		stateString += "State: Add Ground Point";
	}
	else if (state == LES_REMOVE_POINT){
		stateString.clear();
		stateString += "State: Remove Ground Point";
	}
	else if (state == LES_REMOVE_SCENERY){
		stateString.clear();
		stateString += "State: Remove Scenery Object";
	}
	else if (state == LES_MOVE_CAMERA){
		stateString.clear();
		stateString += "State: Move Camera";
	}

	// Update levels camera
	((LevelCamera*)handlers->camera)->update(deltaTime);
}

// Update editor input
void LevelEditor::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH, Handlers* handlers){
	// Get mouse location 
	levelX = ((LevelCamera*)(handlers->camera))->toLevelX(mMouseH->getX());
	levelY = ((LevelCamera*)(handlers->camera))->toLevelY(mMouseH->getY());
	levelLoc.setLocation(levelX, levelY);
	
	// Turn on and off editor
	if (mKeyH->keyReleased(KEY_1))
	{
		if (enabled){
			enabled = false;
			selectedPoint = NULL;
			pointHighlighted = false;
			hide();
			return;
		}
		else{
			enabled = true;
			show();
			return;
		}
	}

	// Grab mouse location 
	mouseLoc.clear();
	mouseLoc += "Mouse:  ";
	mouseLoc += toString((int)mMouseH->getX());
	mouseLoc += ". ";
	mouseLoc += toString((int)mMouseH->getY());
	mouseLoc += "\nLevel: ";
	mouseLoc += toString((int)levelX);
	mouseLoc += ". ";
	mouseLoc += toString((int)levelY);

	if (enabled){
		
		// ---------------------- //
		// Check UI Components 
		// ---------------------- //
		// Update Button input 
		bMove->updateInput(mKeyH, mMouseH);
		bAdd->updateInput(mKeyH, mMouseH);
		bRemove->updateInput(mKeyH, mMouseH);
		bRemoveS->updateInput(mKeyH, mMouseH);
		tTerminal->updateInput(mKeyH, mMouseH);

		if (bMove->wasClicked()){
			state = LES_NONE;
			// Must return so input functions correctly 
			return;
		}
		if (bAdd->wasClicked()){
			state = LES_ADD_POINT;
			// Must return so input functions correctly 
			return;
		}
		if (bRemove->wasClicked()){
			state = LES_REMOVE_POINT;
			// Must return so input functions correctly 
			return;
		}
		if (bRemoveS->wasClicked()){
			state = LES_REMOVE_SCENERY;
			// Must return so input functions correctly 
			return;
		}
		if (tTerminal->CommandIssued()){
			cout << tTerminal->getCommandString() << "\n";
		}


		// ---------------------- //
		// State: None
		// ---------------------- //
		if (state == LES_NONE){
			bool clicked = false;
			if (mMouseH->isLeftDown() && !mMouseH->wasLeftDown())
				clicked = true;
			if (mMouseH->isRightDown() && !mMouseH->wasRightDown()){
				state = LES_MOVE_CAMERA;
				lastMouse.setLocation(mMouseH->getX(), mMouseH->getY());
				return;
			}

			/// Select ground points

			// Reset highlight 
			pointHighlighted = false;

			// Check if mouse is hovering a level ground vertex 
			Point* itr = handlers->ground->getPoints();
			while (itr != NULL){
				// Check if the mouse is close enought to the point to select 
				if (dist(levelLoc, *itr) < maxPointDistance){
				
					// Set hovered point
					pointHighlighted = true;
					// Set display point location 
					pointSprite.setPosition(
						((LevelCamera*)(handlers->camera))->toScreenX(itr->getX()), 
						((LevelCamera*)(handlers->camera))->toScreenY(itr->getY()));

					// Check if mouse was clicked 
					if (clicked){
						selectedPoint = itr;
						state = LES_MOVE_POINT;
						break;
					}
				}
				itr = itr->next;
			}

			/// Select Scenery Objects 

			SceneryHandler* sh = (SceneryHandler*)handlers->sceneryHandler;
			SceneryObject* head = sh->getHead();

			// Check if mouse is hovering a scenery object 
			if (clicked){
				while (head != NULL){
					// Check if scenery object contains mouse And mouse was clicked 
					if (head->getCollisionRec()->contains(levelX, levelY)){
						// Set up editor to move scenery object 
						sceneryOffsetX = head->getX() - levelX;
						sceneryOffsetY = head->getY() - levelY;
						// Set pointer reference
						scObj = head;

						// Change state
						state = LES_SCENERY;
						break;
					}

					head = head->getNext();
				}
			}
		}
		// ---------------------- //
		// State: Move Point
		// ---------------------- //
		else if (state == LES_MOVE_POINT){
			// Check if mouse was released
			if (!mMouseH->isLeftDown()){
				selectedPoint = NULL;
				state = LES_NONE;
			}
			// Move ground point if not 
			else {
				// Wooo giant if.... sorry 
				// Set point x location
				if ((selectedPoint->prev == NULL && levelX < selectedPoint->next->getX()) ||
					(levelX > selectedPoint->prev->getX() && selectedPoint->next == NULL)||
					(levelX > selectedPoint->prev->getX() && levelX < selectedPoint->next->getX()))
					selectedPoint->setX(levelX);
				// Set point y location
				selectedPoint->setY(levelY);
				// Fix Vertexes and cords 
				handlers->ground->fixVertsForPoint(selectedPoint);

				// Set display point location 
				pointSprite.setPosition(mMouseH->getX(), mMouseH->getY());
			}
		}
		// ---------------------- //
		// State: Add Point
		// ---------------------- //
		else if (state == LES_ADD_POINT){
			// Check if mouse was released
			if (!mMouseH->isLeftDown() && mMouseH->wasLeftDown()){
				handlers->ground->add(new Point(levelX,levelY));
			}
		}
		// ---------------------- //
		// State: Remove Point
		// ---------------------- //
		else if (state == LES_REMOVE_POINT){
			// Reset highlight 
			pointHighlighted = false;

			// Check if mouse is hovering a level ground vertex 
			Point* itr = handlers->ground->getPoints();
			while (itr != NULL){
				// Check if the mouse is close enought to the point to select 
				if (dist(levelLoc, *itr) < maxPointDistance){
				
					// Set hovered point
					pointHighlighted = true;
					// Set display point location 
					pointSprite.setPosition(
						((LevelCamera*)(handlers->camera))->toScreenX(itr->getX()), 
						((LevelCamera*)(handlers->camera))->toScreenY(itr->getY()));

					// Check if mouse was clicked and if so remove point
					if (mMouseH->isLeftDown() && !mMouseH->wasLeftDown()){
						handlers->ground->remove(itr);
						break;
					}
				}
				itr = itr->next;
			}
		}
		// ---------------------- //
		// State: Move Scenery
		// ---------------------- //
		else if (state == LES_SCENERY){
			// Check if mouse was released
			if (!mMouseH->isLeftDown()){
				scObj = NULL;
				state = LES_NONE;
			}
			else {
				// Set scenery object location 
				scObj->setLocation(
					levelX + sceneryOffsetX,
					levelY + sceneryOffsetY);
			}
		}
		// ---------------------- //
		// State: Remove Scenery 
		// ---------------------- //
		else if (state == LES_REMOVE_SCENERY){
			/// Select Scenery Objects 

			SceneryHandler* sh = (SceneryHandler*)handlers->sceneryHandler;
			SceneryObject* head = sh->getHead();
			SceneryObject* prev = NULL;

			// Check if mouse is hovering a scenery object 
			if (mMouseH->isLeftDown() && !mMouseH->wasLeftDown()){
				while (head != NULL){
					// Check if scenery object contains mouse
					if (head->getCollisionRec()->contains(levelX, levelY)){
						// Check if scenery object was not first 
						if (prev != NULL){
							prev->setNext(head->getNext());
							head->setNext(NULL);
							delete head;
						}
						// Check if it was 
						else {
							sh->setHead(head->getNext());
						}

						break;
					}

					prev = head;
					head = head->getNext();
				}
			}
		}
		// ---------------------- //
		// State: Move Camera  
		// ---------------------- //
		else if (state == LES_MOVE_CAMERA){
			if (!mMouseH->isRightDown()){
				state = LES_NONE;
				return;
			}


			LevelCamera* c = ((LevelCamera*)(handlers->camera));

			c->setLocation(
				c->getX() - (mMouseH->getX() - lastMouse.getX()),
				c->getY() - (mMouseH->getY() - lastMouse.getY()));
			lastMouse.setLocation(mMouseH->getX(), mMouseH->getY());
		}
	}
}

// Draw editor 
void LevelEditor::draw(GLHandler* mgl, UIAtlas* mUI){
	pointSprite.draw(*mgl);
	
	mUI->bindBuffers(mgl);
	mUI->bindTexture(mgl);

	if (enabled){

		mUI->mTextRender->drawText(*mgl,string("Editor on"), 120,5,0,25.0f);
		mUI->mTextRender->drawText(*mgl,mouseLoc, 120,32.0f,0,25.0f);
		mUI->mTextRender->drawText(*mgl,stateString, 120,88.0f,0,25.0f);
	}

	bMove->draw(mgl, mUI);
	bAdd->draw(mgl, mUI);
	bRemove->draw(mgl, mUI);
	bRemoveS->draw(mgl, mUI);
	tTerminal->draw(mgl, mUI);
}


// Show editor elements
void LevelEditor::show(){
	bMove->show();
	bAdd->show();
	bRemove->show();
	bRemoveS->show();
	tTerminal->show();
}

// Hide editor elements
void LevelEditor::hide(){
	bMove->hide();
	bAdd->hide();
	bRemove->hide();
	bRemoveS->hide();
	tTerminal->hide();
}