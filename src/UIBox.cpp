#include "UIBox.h"


UIBox::UIBox(float x, float y, float w, float h)
{
	loc_x = x;
	loc_y = y;
	width = w;
	height = h;
	cornerWidth = 6.0f;
	mAlpha = 1.0f;
}

UIBox::~UIBox(){}

// Set box alpha
void UIBox::setAlpha(float value){
	mAlpha = value;
}

// Draw box 
void UIBox::draw(GLHandler* mgl, UIAtlas* mUI){
	UITransitionObject::draw(mgl, mUI);

	mgl->setFlatColor(flatColor, flatColor[3] * mAlpha);

	// Draw middle 
	mUI->drawScale2(mgl, UI_REC_M, loc_x + cornerWidth, loc_y + cornerWidth, 
		width - (2.0f * cornerWidth), height - (2.0f * cornerWidth));

	// Draw borders 
	// TB
	mUI->drawScale2(mgl, UI_REC_TB, loc_x + cornerWidth, loc_y, 
		width - (2.0f * cornerWidth), 1.0f);
	// BB
	mUI->drawScale2(mgl, UI_REC_BB, loc_x + cornerWidth, loc_y + height - cornerWidth, 
		width - (2.0f * cornerWidth), 1.0f);
	// LB
	mUI->drawScale2(mgl, UI_REC_LB, loc_x, loc_y + cornerWidth, 
		1.0f, height - (2.0f * cornerWidth));
	// RB
	mUI->drawScale2(mgl, UI_REC_RB, loc_x + width - cornerWidth, loc_y + cornerWidth, 
		1.0f, height - (2.0f * cornerWidth));

	// Draw corners 
	// TL
	mUI->draw(mgl, UI_REC_TL, loc_x, loc_y);
	// TR
	mUI->draw(mgl, UI_REC_TR, loc_x + width - cornerWidth, loc_y);
	// BL
	mUI->draw(mgl, UI_REC_BL, loc_x, loc_y + height - cornerWidth);
	// BR
	mUI->draw(mgl, UI_REC_BR, loc_x + width - cornerWidth, loc_y + height - cornerWidth);
}