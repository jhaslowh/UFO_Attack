#include "Sign.h"


Sign::Sign()
{
	type = "sign";
	text = "none";	
	width = 50.0f, height = 50.0f;
	originX = 25.0f;
	originY = 50.0f;
	imageID = GI_SIGN;
	collides = true;
	drawText = false;

	// Set text variables 
	textColor[0] = .5f;
	textColor[1] = .5f;
	textColor[2] = .5f;
	textColor[3] = 1.0f;

	recColor[0] = 1.0f;
	recColor[1] = 1.0f;
	recColor[2] = 1.0f;
	recColor[3] = 1.0f;

	textSize = 16.0f;
}

Sign::~Sign(){}

// Set sign text
void Sign::setText(std::string t){ text = t;}
// Get sign text
std::string Sign::getText(){return text;}


// Update Handlers 
void Sign::update(float deltaTime, Handlers* handlers){
	textOffX = ((Camera2D*)(handlers->camera))->toScreenX(locX);
	textOffY = ((Camera2D*)(handlers->camera))->toScreenY(locY - originY) - textSize - 10.0f;
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
		mgl->setFlatColor(recColor);
		float textWidth = mUI->mTextRender->measureString(text, textSize);
		// Draw background 
		// Arrow
		mUI->draw(mgl, UII_BUBBLE_ARROW, textOffX - 5.0f, textOffY + textSize - 1.0f);
		glCullFace(GL_FRONT);
		// Left edge
		mUI->drawScale2(mgl, UII_BUBBLE_EDGE, textOffX - (textWidth/2.0f) + 1.0f, textOffY - 3.0f,-1.0f,1.0f);
		glCullFace(GL_BACK);
		// Center 
		mUI->draw(mgl, UII_BUBBLE_EDGE, textOffX + (textWidth/2.0f) - 1.0f, textOffY - 3.0f);
		// Right edge 
		mUI->drawScale2(mgl, UII_BUBBLE_CENTER, textOffX - (textWidth/2.0f), textOffY - 3.0f,textWidth,1.0f);

		// Draw text
		mgl->setFlatColor(textColor);
		mUI->mTextRender->drawText(*mgl, text, 
			textOffX - (textWidth/2.0f), 
			textOffY,0,textSize);

		// Set flat color back to white 
		mgl->setFlatColor(1.0f,1.0f,1.0f,1.0f);
	}
}

// Call when the player collides with the object 
void Sign::onCollide(){
	drawText = true;
}