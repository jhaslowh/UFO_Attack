#pragma once
#include <string>
#include "TextureAtlas.h"
#include "TextRender.h"
#include "VertCordGenerator.h"

// UI Index's
#define UII_BUTTON_NORMAL 0
#define UII_BUTTON_HOVER 1
#define UII_BUTTON_CLICK 2
#define UII_CHECKBOX_NORMAL 3
#define UII_CHECKBOX_CHECKED 4
#define UII_REC 5				// Use for drawing rectangles 
#define UII_LEVEL_ARROW 6
#define UII_POINT 7
#define UII_BUBBLE_CENTER 8
#define UII_BUBBLE_EDGE 9
#define UII_BUBBLE_ARROW 10
// These are used to draw outline boxes 
#define UI_REC_TL 11	// Top left corner
#define UI_REC_TR 12	// Top right corner
#define UI_REC_BL 13	// Bottom left corner
#define UI_REC_BR 14	// Bottom right corner
#define UI_REC_TB 15	// Top border
#define UI_REC_BB 16	// Bottom border
#define UI_REC_LB 17	// Left border
#define UI_REC_RB 18	// Right border
#define UI_REC_M 19		// Middle 
#define UI_CURRENCY_ANIMAL 20
#define UI_CURRENCY_HUMAN 21

class UIAtlas : public TextureAtlas
{
	
public:
	// Text renderer is part of this texture sheet
	// so we use it in here. 
	TextRender* mTextRender;

	UIAtlas();
	virtual ~UIAtlas();

	// Set up the stucture of this atlas 
	void load();
};

