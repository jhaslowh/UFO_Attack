#include "LevelEditor.h"

LevelEditor::LevelEditor()
{
	shrinkSpeed = 5.0f;
	maxPointDistance = 6.0f;
	pointIndex = -1;
	hightlightIndex = -1;
	enabled = true;
	sceneryOffsetX = 0;
	sceneryOffsetY = 0;
	scObj = NULL;

	state = LES_NONE;
}
LevelEditor::~LevelEditor(){}

// Load editor 
void LevelEditor::load(){
	pointSprite.setup(8.0f,8.0f,"images/point.png");
	pointSprite.setOrigin(4.0f,4.0f);
	pointSprite.setColor(.8f,.8f,1.0f,1.0f);
	pointSprite.setScale(0.0f);
}

// Update editor state 
void LevelEditor::update(float deltaTime, Ground* ground){
	// Shrink point sprite if point not selected
	if (hightlightIndex == -1){
		if (pointSprite.getScale() > 0.0f){
			pointSprite.setScale(pointSprite.getScale() - (shrinkSpeed * deltaTime));
			if (pointSprite.getScale() < 0.0f)
				pointSprite.setScale(0.0f);
		}
	}
	// Grow sprite if point is selected 
	else {
		// Set display point location 
		pointSprite.setPosition(
			ground->getPoint(hightlightIndex).getX(), 
			ground->getPoint(hightlightIndex).getY());
		
		// Grow sprite 
		if (pointSprite.getScale() < 1.25f){
			pointSprite.setScale(pointSprite.getScale() + (shrinkSpeed * deltaTime));
			if (pointSprite.getScale() > 1.25f)
				pointSprite.setScale(1.25f);
		}
	}
}

// Update editor input
void LevelEditor::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH, Handlers* handlers){
	// Turn on and off editor
	if (mKeyH->keyPressed(KEY_1))
	{
		if (enabled){
			enabled = false;
			pointIndex = -1;
			hightlightIndex = -1;
		}
		else
			enabled = true;
	}

	// Grab mouse location 
	mouseLoc.clear();
	mouseLoc += "Mouse:  ";
	mouseLoc += toString((int)mMouseH->getX());
	mouseLoc += ". ";
	mouseLoc += toString((int)mMouseH->getY());

	if (enabled){
		if (state == LES_NONE){
			bool clicked = false;
			if (mMouseH->isLeftDown() && !mMouseH->wasLeftDown())
				clicked = true;

			/// Select ground points

			// Reset highlight index
			hightlightIndex = -1;

			// Check if mouse is hovering a level ground vertex 
			for (int i = 0; i < handlers->ground->getPointCount(); i++){

				// Check if the mouse is close enought to the point to select 
				if (dist(mMouseH->getLoc(), handlers->ground->getPoint(i)) < maxPointDistance){
				
					// Set hovered point
					hightlightIndex = i;

					// Check if mouse was clicked 
					if (clicked){
						pointIndex = i;
						state = LES_POINT;
						break;
					}
				}
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
		else if (state == LES_POINT){
			// Check if mouse was released
			if (!mMouseH->isLeftDown()){
				pointIndex = -1;
				state = LES_NONE;
			}
			// Move ground point if not 
			else {
				handlers->ground->setPoint(pointIndex, mMouseH->getLoc());
			}
		}
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

	if (enabled){
		mUI->bindBuffers(mgl);
		mUI->bindTexture(mgl);
		mUI->mTextRender->drawText(*mgl,string("Editor on"), 0,0,0,25.0f);
		mUI->mTextRender->drawText(*mgl,mouseLoc, 0,27.0f,0,25.0f);
	}
}