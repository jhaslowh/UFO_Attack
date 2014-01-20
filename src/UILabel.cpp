#include "UILabel.h"

UILabel::UILabel(string str) : UITransitionObject(){
	text = str;
	textSize = 25.0f;
}
UILabel::~UILabel(){}

// Getters and setters 
string UILabel::getText(){return text;}
void UILabel::setText(string l){text = l;}
float UILabel::getTextSize(){return textSize;}
void UILabel::setTextSize(float size){textSize = size;}

// Draw the object to the screen
// UIAtles must be bound first.
void UILabel::draw(GLHandler* mgl, UIAtlas* mAtlas){
	UITransitionObject::draw(mgl, mAtlas);

	UIAtlas* mUI = (UIAtlas*)mAtlas;
	mgl->setFlatColor(flatColor);
	mUI->mTextRender->drawText(*mgl, text,
		loc_x, loc_y, 0, textSize);
}