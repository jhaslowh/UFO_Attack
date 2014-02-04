#include "Sign.h"


Sign::Sign()
{
	text = "none";	
	width = 50.0f, height = 50.0f;
	originX = 25.0f;
	originY = 50.0f;
	imageID = GI_SIGN;
	collides = false;
	drawText = false;

	// Set text variables 
	textColor[0] = 1.0f;
	textColor[1] = 1.0f;
	textColor[2] = 1.0f;
	textColor[3] = .7f;

	recColor[0] = .3f;
	recColor[1] = .3f;
	recColor[2] = .3f;
	recColor[3] = .7f;

	textSize = 16.0f;
}

Sign::~Sign(){}

// Set sign text
void Sign::setText(string t){ text = t;}
// Get sign text
string Sign::getText(){return text;}


// Update Handlers 
void Sign::update(float deltaTime, Handlers* handlers){
	textOffX = ((Camera2D*)(handlers->camera))->toScreenX(locX);
	textOffY = ((Camera2D*)(handlers->camera))->toScreenY(locY) - originY;
}


// Update scenery input 
void Sign::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH, Handlers* handlers){
	
	fixCollRec();

	// Check if mouse is on sign
	if (collisionRec->contains(
		((Camera2D*)(handlers->camera))->toLevelX(mMouseH->getX()),
		((Camera2D*)(handlers->camera))->toLevelY(mMouseH->getY()))){
		drawText = true;
	}
	else 
		drawText = false;
}

// Draw object ui elements 
void Sign::drawUI(GLHandler* mgl, UIAtlas* mUI){
	if (drawText){
		float textWidth = mUI->mTextRender->measureString(text, textSize);
		// Draw background 
		mgl->setFlatColor(recColor);
		mUI->drawScale2(mgl, UII_REC, 
			textOffX - (textWidth/2.0f) - 4.0f,
			textOffY - 4.0f,textWidth + 8.0f, textSize + 8.0f);
		// Draw text
		mgl->setFlatColor(textColor);
		mUI->mTextRender->drawText(*mgl, text, 
			textOffX - (textWidth/2.0f), 
			textOffY,0,textSize);

		// Set flat color back to white 
		mgl->setFlatColor(1.0f,1.0f,1.0f,1.0f);
	}
}