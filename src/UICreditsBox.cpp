#include "UICreditsBox.h"


UICreditsBox::UICreditsBox() : UIObject()
{
	title = "none";
	subtitle = "none";
	textSize = 30.0f;
}
UICreditsBox::UICreditsBox(std::string t, std::string s) : UIObject()
{
	title = t;
	subtitle = s;
	textSize = 30.0f;

	// Calculate text height 
	int length = subtitle.length();
	int count = 2;
	if (length > 0){
		for (int i = 0; i < length; i++){
			if (subtitle.at(i) == '\n'){
				count++;
			}
		}
	}
	height = count * textSize;
}

UICreditsBox::~UICreditsBox(){}

// Call to reset up credits box 
void UICreditsBox::setup(std::string t, std::string s){
	title = t;
	subtitle = s;

	// Calculate text height 
	int length = subtitle.length();
	int count = 2;
	if (length > 0){
		for (int i = 0; i < length; i++){
			if (subtitle.at(i) == '\n'){
				count++;
			}
		}
	}
	height = count * textSize;
}

// Draw the object to the screen
// UIAtles must be bound first.
void UICreditsBox::draw(GLHandler* mgl, UIAtlas* mAtlas){
	UIObject::draw(mgl, mAtlas);

	UIAtlas* mUI = (UIAtlas*)mAtlas;
	mgl->setFlatColor(COLOR_UI_BLUE);
	mUI->mTextRender->drawText(*mgl, title, loc_x, loc_y, 0.0f, textSize);	
	mgl->setFlatColor(COLOR_UI_LABEL);
	mUI->mTextRender->drawText(*mgl, subtitle, loc_x, loc_y + textSize, 0.0f, textSize);	
}

// Draw the object to the screen at sent offset.
// UIAtles must be bound first.
void UICreditsBox::draw(GLHandler* mgl, UIAtlas* mAtlas, float offx, float offy){
	UIObject::draw(mgl, mAtlas, offx, offy);

	UIAtlas* mUI = (UIAtlas*)mAtlas;
	mgl->setFlatColor(COLOR_UI_BLUE);
	mUI->mTextRender->drawText(*mgl, title, loc_x + offx, loc_y + offy, 0.0f, textSize);	
	mgl->setFlatColor(COLOR_UI_LABEL);
	mUI->mTextRender->drawText(*mgl, subtitle, loc_x + offx, loc_y  + textSize + offy, 0.0f, textSize);	
}
