#include "TutBox.h"


TutBox::TutBox()
{
	text = "";
	locX = locY = 0.0f;
	width = height = 0.0f;
	showArrow = false;
	arrowRotation = arrowOffsetX = arrowOffsetY = 0.0f;
}

TutBox::TutBox(std::string t){
	text = t;
	locX = locY = 0.0f;
	width = height = 0.0f;
	showArrow = false;
	arrowRotation = arrowOffsetX = arrowOffsetY = 0.0f;
}
	
TutBox::TutBox(std::string t, float w, float h){
	text = t;
	locX = locY = 0.0f;
	width = w;
	height = h;
	showArrow = false;
	arrowRotation = arrowOffsetX = arrowOffsetY = 0.0f;
}

TutBox::~TutBox()
{

}

void TutBox::setText(std::string s){text = s;}
std::string TutBox::getText(){return text;}
void TutBox::setLocation(float x, float y){locX = x; locY = y;}
void TutBox::setX(float x){locX = x;}
float TutBox::getX(){return locX;}
void TutBox::setY(float y){locY = y;}
float TutBox::getY(){return locY;}
void TutBox::setSize(float w, float h){width = w; height = h;}
void TutBox::setWidth(float w){width = w;}
float TutBox::getWidth(){return width;}
void TutBox::setHeight(float h){height = h;}
float TutBox::getHeight(){return height;}

// Draw ui box 
void TutBox::draw(GLHandler* mgl, UIAtlas* mUI){
	mgl->setFlatColor(COLOR_BLACK_10);
	mUI->drawScale2(mgl,UII_REC,locX+4.0f, locY+4.0f, width, height);
	if (showArrow)
		mUI->draw(mgl,UII_TUT_ARROW, arrowOffsetX+4.0f, arrowOffsetY+4.0f,1.0f, arrowRotation);
	mgl->setFlatColor(COLOR_BLACK_50);
	mUI->drawScale2(mgl,UII_REC,locX, locY, width, height);
	if (showArrow)
		mUI->draw(mgl,UII_TUT_ARROW, arrowOffsetX, arrowOffsetY,1.0f, arrowRotation);

	mgl->setFlatColor(COLOR_UI_LABEL);
	mUI->mTextRender->drawText(*mgl,text,locX+4.0f,locY+4.0f,0.0f,TUT_BOX_TEXT_SIZE);
}


// Turn on the tut arrow and put it at the sent loc
// loc = TA_TOP_LEFT, TA_TOP_MIDDLE, TA_RIGHT_TOP 
// NOTE: Call this after size and location set 
void TutBox::turnOnTutArrow(int loc){
	switch (loc){
		case TA_TOP_LEFT:
			showArrow = true;
			arrowRotation = 0.0f;
			arrowOffsetX = locX;
			arrowOffsetY = locY - 19.0f;
			break;
		case TA_TOP_MIDDLE:
			showArrow = true;
			arrowRotation = 0.0f;
			arrowOffsetX = locX + (width*.5f) - 10.0f;
			arrowOffsetY = locY - 19.0f;
			break;
		case TA_RIGHT_TOP:
			showArrow = true;
			arrowRotation = 90.0f;
			arrowOffsetX = locX + width + 19.0f;
			arrowOffsetY = locY;
			break;
		default:
			showArrow = false;
			break;
	}
}

// Turn off arrow
void TutBox::turnOffTutArrow(){
	showArrow = false;
}
