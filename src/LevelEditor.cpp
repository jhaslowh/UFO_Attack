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

	state = LES_NONE;
}
LevelEditor::~LevelEditor(){
	delete bMove;
	delete bAdd;
	delete bRemove;
}

// Setup basic structures
void LevelEditor::init(){
	bMove = new UIButton(5,5,100.0f,35.0f, std::string("Move Obj"));
	bMove->setupHide(HT_HOROZONTAL,bMove->getX()-100.0f,.2f,true);
	bMove->setHidden();

	bAdd = new UIButton(5,45.0f,100.0f,35.0f, std::string("Add"));
	bAdd->setupHide(HT_HOROZONTAL,bAdd->getX()-100.0f,.2f,true);
	bAdd->setHidden();

	bRemove = new UIButton(5,85.0f,100.0f,35.0f, std::string("Remove"));
	bRemove->setupHide(HT_HOROZONTAL,bRemove->getX()-100.0f,.2f,true);
	bRemove->setHidden();
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
}

// Update editor state 
void LevelEditor::update(float deltaTime, Ground* ground){
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
		// Set display point location 
		if (selectedPoint != NULL)
			pointSprite.setPosition(selectedPoint->getX(), selectedPoint->getY());
		
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
}

// Update editor input
void LevelEditor::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH, Handlers* handlers){
	// Update Button input 
	bMove->updateInput(mKeyH, mMouseH);
	bAdd->updateInput(mKeyH, mMouseH);
	bRemove->updateInput(mKeyH, mMouseH);

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
	
	// Turn on and off editor
	if (mKeyH->keyPressed(KEY_1))
	{
		if (enabled){
			enabled = false;
			selectedPoint = NULL;
			pointHighlighted = false;
			bMove->hide();
			bAdd->hide();
			bRemove->hide();
		}
		else{
			enabled = true;
			bMove->show();
			bAdd->show();
			bRemove->show();
		}
	}

	// Grab mouse location 
	mouseLoc.clear();
	mouseLoc += "Mouse:  ";
	mouseLoc += toString((int)mMouseH->getX());
	mouseLoc += ". ";
	mouseLoc += toString((int)mMouseH->getY());

	if (enabled){
		// ---------------------- //
		// State: None
		// ---------------------- //
		if (state == LES_NONE){
			bool clicked = false;
			if (mMouseH->isLeftDown() && !mMouseH->wasLeftDown())
				clicked = true;

			/// Select ground points

			// Reset highlight 
			pointHighlighted = false;

			// Check if mouse is hovering a level ground vertex 
			Point* itr = handlers->ground->getPoints();
			while (itr != NULL){
				// Check if the mouse is close enought to the point to select 
				if (dist(mMouseH->getLoc(), *itr) < maxPointDistance){
				
					// Set hovered point
					pointHighlighted = true;
					pointSprite.setPosition(itr->getX(), itr->getY());

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
					if (head->getCollisionRec()->contains(mMouseH->getX(), mMouseH->getY())){
						// Set up editor to move scenery object 
						sceneryOffsetX = head->getX() - mMouseH->getX();
						sceneryOffsetY = head->getY() - mMouseH->getY();
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
				if ((selectedPoint->prev == NULL && mMouseH->getX() < selectedPoint->next->getX()) ||
					(mMouseH->getX() > selectedPoint->prev->getX() && selectedPoint->next == NULL)||
					(mMouseH->getX() > selectedPoint->prev->getX() && mMouseH->getX() < selectedPoint->next->getX()))
					selectedPoint->setX(mMouseH->getX());
				// Set point y location
				selectedPoint->setY(mMouseH->getY());
				// Fix Vertexes and cords 
				handlers->ground->fixVertsForPoint(selectedPoint);
			}
		}
		// ---------------------- //
		// State: Add Point
		// ---------------------- //
		else if (state == LES_ADD_POINT){
			// Check if mouse was released
			if (!mMouseH->isLeftDown() && mMouseH->wasLeftDown()){
				handlers->ground->add(new Point(mMouseH->getX(), mMouseH->getY()));
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
				if (dist(mMouseH->getLoc(), *itr) < maxPointDistance){
				
					// Set hovered point
					pointHighlighted = true;
					pointSprite.setPosition(itr->getX(), itr->getY());

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
					mMouseH->getX() + sceneryOffsetX,
					mMouseH->getY() + sceneryOffsetY);
			}
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
		mUI->mTextRender->drawText(*mgl,stateString, 120,60.0f,0,25.0f);
	}

	bMove->draw(mgl, mUI);
	bAdd->draw(mgl, mUI);
	bRemove->draw(mgl, mUI);
}