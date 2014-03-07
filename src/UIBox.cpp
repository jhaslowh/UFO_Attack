#include "UIBox.h"


UIBox::UIBox(float x, float y, float w, float h)
{
	loc_x = x;
	loc_y = y;
	width = w;
	height = h;
	cornerWidth = 6.0f;
}

UIBox::~UIBox(){}

// Draw box 
void UIBox::draw(GLHandler* mgl, UIAtlas* mUI){
	UITransitionObject::draw(mgl, mUI);

	mgl->setFlatColor(flatColor, flatColor[3] * mOpacity);

	// Draw middle 
	mUI->drawScale2(mgl, UII_REC_M, loc_x + cornerWidth, loc_y + cornerWidth, 
		width - (2.0f * cornerWidth), height - (2.0f * cornerWidth));

	// Draw borders 
	// TB
	mUI->drawScale2(mgl, UII_REC_TB, loc_x + cornerWidth, loc_y, 
		width - (2.0f * cornerWidth), 1.0f);
	// BB
	mUI->drawScale2(mgl, UII_REC_BB, loc_x + cornerWidth, loc_y + height - cornerWidth, 
		width - (2.0f * cornerWidth), 1.0f);
	// LB
	mUI->drawScale2(mgl, UII_REC_LB, loc_x, loc_y + cornerWidth, 
		1.0f, height - (2.0f * cornerWidth));
	// RB
	mUI->drawScale2(mgl, UII_REC_RB, loc_x + width - cornerWidth, loc_y + cornerWidth, 
		1.0f, height - (2.0f * cornerWidth));

	// Draw corners 
	// TL
	mUI->draw(mgl, UII_REC_TL, loc_x, loc_y);
	// TR
	mUI->draw(mgl, UII_REC_TR, loc_x + width - cornerWidth, loc_y);
	// BL
	mUI->draw(mgl, UII_REC_BL, loc_x, loc_y + height - cornerWidth);
	// BR
	mUI->draw(mgl, UII_REC_BR, loc_x + width - cornerWidth, loc_y + height - cornerWidth);
}

// Draw box at offset 
void UIBox::draw(GLHandler* mgl, UIAtlas* mUI, float offx, float offy){
	UIObject::draw(mgl, mUI, offx, offy);

	mgl->setFlatColor(flatColor, flatColor[3] * mOpacity);

	// Draw middle 
	mUI->drawScale2(mgl, UII_REC_M, offx + loc_x + cornerWidth, offy + loc_y + cornerWidth, 
		width - (2.0f * cornerWidth), height - (2.0f * cornerWidth));

	// Draw borders 
	// TB
	mUI->drawScale2(mgl, UII_REC_TB, offx + loc_x + cornerWidth,  offy + loc_y, 
		width - (2.0f * cornerWidth), 1.0f);
	// BB
	mUI->drawScale2(mgl, UII_REC_BB, offx + loc_x + cornerWidth, offy + loc_y + height - cornerWidth, 
		width - (2.0f * cornerWidth), 1.0f);
	// LB
	mUI->drawScale2(mgl, UII_REC_LB, offx + loc_x, offy + loc_y + cornerWidth, 
		1.0f, height - (2.0f * cornerWidth));
	// RB
	mUI->drawScale2(mgl, UII_REC_RB, offx + loc_x + width - cornerWidth, offy + loc_y + cornerWidth, 
		1.0f, height - (2.0f * cornerWidth));

	// Draw corners 
	// TL
	mUI->draw(mgl, UII_REC_TL, offx + loc_x, offy + loc_y);
	// TR
	mUI->draw(mgl, UII_REC_TR, offx + loc_x + width - cornerWidth, offy + loc_y);
	// BL
	mUI->draw(mgl, UII_REC_BL, offx + loc_x, offy + loc_y + height - cornerWidth);
	// BR
	mUI->draw(mgl, UII_REC_BR, offx + loc_x + width - cornerWidth, offy + loc_y + height - cornerWidth);
}