#include "LevelEditor.h"

using namespace std;

LevelEditor::LevelEditor()
{
	shrinkSpeed = 5.0f;
	maxPointDistance = 6.0f;
	selectedPoint = NULL;
	pointHighlighted = false;
	enabled = false;
	mouseOffsetX = 0;
	mouseOffsetY = 0;
	scObj = NULL;
	movingCamera = false;

	levelX = 0.0f;
	levelY = 0.0f;

	boundDistance = 40.0f;

	screenWidth = 0.0f;
	screenHeight = 0.0f;

	zoomPerScroll = .1f;

	state = LES_NONE;
	bMove = NULL;
	bAdd = NULL;
	bRemove = NULL;
}
LevelEditor::~LevelEditor(){
	delete bMove;
	delete bAdd;
	delete bRemove;
}

// Set handlers for editor 
void LevelEditor::setHandlers(Handlers* handlers){
	camera = (Camera2D*)(handlers->camera);
	sceneryHandler = (SceneryHandler*)(handlers->sceneryHandler);
	levelProps = (LevelProperties*)(handlers->levelProps);
	ground = (Ground*)handlers->ground;
	npcHandler = (NPCHandler*)(handlers->npcHandler);
	this->handlers = handlers;
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

	levelLeft.setPosition(0.0f,screen_height/2.0f);
	levelRight.setPosition(0.0f,screen_height/2.0f);

	screenWidth = screen_width;
	screenHeight = screen_height;
}

// Load editor 
void LevelEditor::load(TextureAtlas* mAtlas){
	pointSprite.setID(UII_POINT);
	pointSprite.setOrigin(4.0f,4.0f);
	pointSprite.setScale(0.0f);
	pointColor[0] = .8f;
	pointColor[1] = .8f;
	pointColor[2] = 1.0f;
	pointColor[3] = 1.0f;

	levelLeft.setOrigin(0.0f,32.0f);
	levelLeft.setRotation(180.0f);
	levelLeft.setID(UII_LEVEL_ARROW);

	levelRight.setOrigin(0.0f,32.0f);
	levelRight.setID(UII_LEVEL_ARROW);
	
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

	// Update State string 
	if (state == LES_NONE || state == LES_MOVE_POINT || state == LES_SCENERY)
		stateString = "State: Move Object";
	else if (state == LES_ADD_POINT)
		stateString = "State: Add Ground Point";
	else if (state == LES_REMOVE_POINT)
		stateString = "State: Remove Ground Point";
	else if (state == LES_REMOVE_SCENERY)
		stateString = "State: Remove Scenery Object";
	else if (state == LES_LB_LEFT || state == LES_LB_RIGHT)
		stateString = "State: Moving Level Bounds";

	// Update levels camera
	((Camera2D*)handlers->camera)->update(deltaTime);

	// Set level sprite locations 
	levelLeft.setX(((Camera2D*)(handlers->camera))->toScreenX(
		((LevelProperties*)(handlers->levelProps))->getLevelLeft()  ));
	levelRight.setX(((Camera2D*)(handlers->camera))->toScreenX(
		((LevelProperties*)(handlers->levelProps))->getLevelRight()  ));
}

// Update editor input
void LevelEditor::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH, Handlers* handlers){
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
	if (enabled){
		// Check for zoom 
		if (mMouseH->scrollDown()){
			camera->setZoom(camera->getZoom() - zoomPerScroll);
		}
		if (mMouseH->scrollUp()){
			camera->setZoom(camera->getZoom() + zoomPerScroll);
		}

		// Get mouse location 
		levelX = ((Camera2D*)(handlers->camera))->toLevelX(mMouseH->getX());
		levelY = ((Camera2D*)(handlers->camera))->toLevelY(mMouseH->getY());
		levelLoc.setLocation(levelX, levelY);

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
		
		// ---------------------- //
		// Check UI Components 
		// ---------------------- //
		// Update Button input 
		bMove->updateInput(mKeyH, mMouseH);
		bAdd->updateInput(mKeyH, mMouseH);
		bRemove->updateInput(mKeyH, mMouseH);
		bRemoveS->updateInput(mKeyH, mMouseH);

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

		// Move camera 
		if (movingCamera){
			if (!mMouseH->isRightDown()){
				movingCamera = false;
			}
			else {
				// Get camera reference
				Camera2D* c = ((Camera2D*)(handlers->camera));

				// Mover camera 
				c->setLocation(
					c->getX() - (mMouseH->getX() - lastMouse.getX()),
					c->getY() - (mMouseH->getY() - lastMouse.getY()));
				lastMouse.setLocation(mMouseH->getX(), mMouseH->getY());
			}
		}
		// Check if user is trying to move camera 
		else {
			if (mMouseH->isRightDown() && !mMouseH->wasRightDown()){
				movingCamera = true;
				lastMouse.setLocation(mMouseH->getX(), mMouseH->getY());
			}
		}

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
				if (dist(levelLoc, *itr) < maxPointDistance){
				
					// Set hovered point
					pointHighlighted = true;
					// Set display point location 
					pointSprite.setPosition(
						((Camera2D*)(handlers->camera))->toScreenX(itr->getX()), 
						((Camera2D*)(handlers->camera))->toScreenY(itr->getY()));

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
						mouseOffsetX = head->getX() - levelX;
						mouseOffsetY = head->getY() - levelY;
						// Set pointer reference
						scObj = head;

						// Change state
						state = LES_SCENERY;
						break;
					}

					head = head->getNext();
				}
			}

			/// Select Level Bounds 
			if (clicked){
				if (dist(mMouseH->getLoc(), Point(levelLeft.getX()-32.0f, levelLeft.getY()))
					<= boundDistance){
					state = LES_LB_LEFT;
					mouseOffsetX = levelLeft.getX() - mMouseH->getX();
					return;
				}
		
				if (dist(mMouseH->getLoc(), Point(levelRight.getX()+32.0f, levelRight.getY()))
					<= boundDistance){
					state = LES_LB_RIGHT;
					mouseOffsetX = levelRight.getX() - mMouseH->getX();
					return;
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
						((Camera2D*)(handlers->camera))->toScreenX(itr->getX()), 
						((Camera2D*)(handlers->camera))->toScreenY(itr->getY()));

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
					levelX + mouseOffsetX,
					levelY + mouseOffsetY);
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
		// State: Move Level Bounds   
		// ---------------------- //
		else if (state == LES_LB_LEFT){
			if (!mMouseH->isLeftDown()){
				state = LES_NONE;
				return;
			}

			// Set bounds location 
			((LevelProperties*)(handlers->levelProps))->setLevelLeft
				(((Camera2D*)(handlers->camera))->toLevelX(mMouseH->getX()+ mouseOffsetX));
		}
		else if (state == LES_LB_RIGHT){
			if (!mMouseH->isLeftDown()){
				state = LES_NONE;
				return;
			}
			
			// Set bounds location 
			((LevelProperties*)(handlers->levelProps))->setLevelRight
				(((Camera2D*)(handlers->camera))->toLevelX(mMouseH->getX()+ mouseOffsetX));
		}
	}
}

// Draw editor 
void LevelEditor::draw(GLHandler* mgl, UIAtlas* mUI){
	if (enabled){
		// Draw all ground points 
		mgl->setFlatColor(COLOR_BLACK);
		Point* itr = ground->getPoints();
		float sx, sy;
		while (itr != NULL){
			// Convert point location to screen coords 
			sx = camera->toScreenX(itr->getX());
			sy = camera->toScreenY(itr->getY());

			// Draw point if on screen 
			if (sx >= 0 && sx <= levelProps->getScreenWidth() &&
				sy >= 0 && sy <= levelProps->getScreenHeight())
				mUI->draw(mgl, UII_POINT, sx, sy, 1.0f, 0.0f, 4.0f, 4.0f);

			// move to next point
			itr = itr->next;
		}

		// Draw selected point
		mgl->setFlatColor(pointColor);
		pointSprite.draw(mgl, mUI);
		// Draw level boundary sprites
		mgl->setFlatColor(1.0f,1.0f,1.0f,1.0f);
		levelLeft.draw(mgl, mUI);
		levelRight.draw(mgl, mUI);

		// Draw editor text
		mUI->mTextRender->drawText(*mgl,string("Editor on"), 120,5,0,25.0f);
		mUI->mTextRender->drawText(*mgl,mouseLoc, 120,32.0f,0,25.0f);
		mUI->mTextRender->drawText(*mgl,stateString, 120,88.0f,0,25.0f);
	}

	// Draw UI buttons 
	bMove->draw(mgl, mUI);
	bAdd->draw(mgl, mUI);
	bRemove->draw(mgl, mUI);
	bRemoveS->draw(mgl, mUI);
}


// Parse a command give
bool LevelEditor::parseCommand(UITerminal* terminal, string command, string args){

	// Variables 
	string subCommand("none");
	string subArgs("none");

	// Check for scenery command 
	if (command == "scenery"){
		// No arguments given
		if (args == "none"){
			terminal->addLine("No arguments given to command: scenery", TL_WARNING);
			return true;
		}

		// Grab commands and args 
		UITerminal::getCommandAndArgs(&args, &subCommand, &subArgs);

		// Check commands 
		if (subCommand == "add"){
			UITerminal::getCommandAndArgs(&subArgs, &subCommand, &subArgs);

			// Add new scenery object 
			if (sceneryHandler->add(subCommand,subArgs,
				camera->toLevelX(screenWidth/2.0f), camera->toLevelY(screenHeight/2.0f))){
				terminal->addLine(command + " " + args, TL_SUCCESS);
				return true;
			}

			terminal->addLine("Unrecognized arguments given to command: scenery add", TL_WARNING);
			terminal->addLine("scenery add " + subCommand + " " + subArgs, TL_WARNING);
			return true;
		}

		terminal->addLine("Unrecognized arguments given to command: scenery", TL_WARNING);
		terminal->addLine("scenery " + args, TL_WARNING);
		return true;
	}
	// Check for editor commands 
	else if (command == "editor"){
		// No arguments given
		if (args == "none"){
			terminal->addLine("No arguments given to command: editor", TL_WARNING);
			return true;
		}

		// Close the editor 
		if (args == "close"){
			enabled = false;
			hide();
			terminal->addLine("editor close", TL_SUCCESS);
			return true;
		}
		// Open the editor 
		else if (args == "open"){
			enabled = true;
			show();
			terminal->addLine("editor open", TL_SUCCESS);
			return true;
		}

		terminal->addLine("scenery " + args, TL_WARNING);
		terminal->addLine("Unrecognized arguments given to command: scenery", TL_WARNING);
		return true;
	}
	//Check for save data
	else if (command=="saveFile")
	{
		// No arguments given
		if (args == "none"){
			terminal->addLine("No arguments given to command: saveFile", TL_WARNING);
			terminal->addLine(command, TL_WARNING);
			return true;
		}
		//filename given
		else
		{
			terminal->addLine("Writing level to file... ", TL_SUCCESS);
			saveLevel(handlers, args, true);
			terminal->addLine("Save successful", TL_SUCCESS);
			return true;
		}
	}
	// Check for save level command 
	else if (command == "save"){
		if (args != "none"){
			terminal->addLine("Writing level to file... ", TL_SUCCESS);
			saveLevel(handlers, args, false);
			terminal->addLine("Save successful", TL_SUCCESS);
			return true;
		}
		terminal->addLine("No arguments given to command: save", TL_WARNING);
		terminal->addLine(command, TL_WARNING);
		return true;
	}
	// Check for npc command
	else if (command == "npc"){
		// No arguments given
		if (args == "none"){
			terminal->addLine("No arguments given to command: npc", TL_WARNING);
			return true;
		}

		// Grab commands and args 
		UITerminal::getCommandAndArgs(&args, &subCommand, &subArgs);

		// Check commands 
		if (subCommand == "add"){
			UITerminal::getCommandAndArgs(&subArgs, &subCommand, &subArgs);

			if (npcHandler->addByName(subCommand,
				camera->toLevelX(screenWidth/2.0f), camera->toLevelY(screenHeight/2.0f))){
				// Increment enemy level count
				levelProps->setEnemyCount(levelProps->getEnemyCount() + 1);
				// Add success line to terminal
				terminal->addLine(command + " " + args, TL_SUCCESS);
				return true;
			}
			else {
				terminal->addLine(command + " " + args, TL_WARNING);
				return true;
			}
		}
	}

	return false;
}


// Show editor elements
void LevelEditor::show(){
	bMove->show();
	bAdd->show();
	bRemove->show();
	bRemoveS->show();
}

// Hide editor elements
void LevelEditor::hide(){
	bMove->hide();
	bAdd->hide();
	bRemove->hide();
	bRemoveS->hide();
}