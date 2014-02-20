#include "UILabel.h"

UILabel::UILabel(std::string str) : UITransitionObject(){
	text = str;
	textSize = 25.0f;
}
UILabel::~UILabel(){}

// Getters and setters 
std::string UILabel::getText(){return text;}
void UILabel::setText(std::string l){text = l;}
float UILabel::getTextSize(){return textSize;}
void UILabel::setTextSize(float size){textSize = size;}

// Draw the object to the screen
// UIAtles must be bound first.
void UILabel::draw(GLHandler* mgl, UIAtlas* mAtlas){
	UITransitionObject::draw(mgl, mAtlas);

	UIAtlas* mUI = (UIAtlas*)mAtlas;
	mgl->setFlatColor(flatColor, flatColor[3] * mOpacity);
	mUI->mTextRender->drawText(*mgl, text,
		loc_x, loc_y, 0, textSize);
}

// Draw the object to the screen at sent offset.
// UIAtles must be bound first.
void UILabel::draw(GLHandler* mgl, UIAtlas* mAtlas, float offx, float offy){
	UIObject::draw(mgl, mAtlas, offx, offy);
	
	UIAtlas* mUI = (UIAtlas*)mAtlas;
	mgl->setFlatColor(flatColor, flatColor[3] * mOpacity);
	mUI->mTextRender->drawText(*mgl, text,
		offx + loc_x, offy + loc_y, 0, textSize);
}